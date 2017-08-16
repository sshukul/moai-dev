// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAICollisionPrim.h>
#include <moai-sim/MOAICollisionProp.h>
#include <moai-sim/MOAICollisionShape.h>

//================================================================//
// MOAICollisionPrimVisitor
//================================================================//

//----------------------------------------------------------------//
MOAICollisionPrimVisitor::MOAICollisionPrimVisitor () :
	mProp0 ( 0 ),
	mProp1 ( 0 ) {
}

//----------------------------------------------------------------//
MOAICollisionPrimVisitor::~MOAICollisionPrimVisitor () {
}

//----------------------------------------------------------------//
void MOAICollisionPrimVisitor::Process ( const MOAICollisionPrim& shape0, const MOAICollisionPrim& shape1, const ZLAffine3D& t0, const ZLAffine3D& t1 ) {

	this->MOAICollisionPrimVisitor_Process ( shape0, shape1, t0, t1 );
}

//----------------------------------------------------------------//
void MOAICollisionPrimVisitor::Process ( MOAICollisionProp& prop0, MOAICollisionProp& prop1 ) {

	this->SetProps ( &prop0, &prop1 );

	const MOAICollisionShape* shape0 = prop0.GetCollisionShape ();
	const MOAICollisionShape* shape1 = prop1.GetCollisionShape ();
	
	ZLAffine3D t0 = prop0.GetLocalToWorldMtx ();
	ZLAffine3D t1 = prop1.GetLocalToWorldMtx ();
	
	if ( shape0 || shape1 ) {
	
		if ( shape0 && shape1 ) {
		
			this->Process ( *shape0, *shape1, t0, t1 );
		}
		else if ( shape0 ){
		
			ZLBounds bounds = prop1.GetModelBounds ();
			this->Process ( *shape0, bounds, t0, t1 );
		}
		else if ( shape1 ) {
		
			ZLBounds bounds = prop0.GetModelBounds ();
			this->Process ( *shape1, bounds, t0, t1 );
		}
	}
	else {
	
		MOAIOverlapBox box0;
		box0.mShape = prop0.GetModelBounds ();
		box0.mBounds = box0.mShape;
		
		MOAIOverlapBox box1;
		box1.mShape = prop1.GetModelBounds ();
		box1.mBounds = box1.mShape;
		
		this->Process ( box0, box1, t0, t1 );
	}
}

//----------------------------------------------------------------//
void MOAICollisionPrimVisitor::Process ( const MOAICollisionShape& shape0, const ZLBox& bounds1, const ZLAffine3D& t0, const ZLAffine3D& t1 ) {

	MOAIOverlapBox shape1;
	shape1.mShape = bounds1;
	shape1.mBounds = bounds1;

	size_t shapeCount0 = shape0.mShapes.Size ();

	if ( shapeCount0 == 1 ) {
	
		this->Process ( *shape0.mShapes [ 0 ], shape1, t0, t1 );
	}
	else {
	
		for ( size_t i = 0; i < shapeCount0; ++i ) {
			this->Process ( *shape0.mShapes [ i ], shape1, t0, t1 );
		}
	}
}

//----------------------------------------------------------------//
void MOAICollisionPrimVisitor::Process ( const MOAICollisionShape& shape0, const MOAICollisionShape& shape1, const ZLAffine3D& t0, const ZLAffine3D& t1 ) {

	size_t shapeCount0 = shape0.mShapes.Size ();
	size_t shapeCount1 = shape1.mShapes.Size ();
	
	if (( shapeCount0 == 1 ) || ( shapeCount1 == 1 )) {
	
		if (( shapeCount0 == 1 ) && ( shapeCount1 == 1 )) {
		
			this->Process ( *shape0.mShapes [ 0 ], *shape1.mShapes [ 0 ], t0, t1 );
		}
		else if ( shapeCount1 == 1 ) {
		
			for ( size_t i = 0; i < shapeCount0; ++i ) {
				this->Process ( *shape0.mShapes [ i ], *shape1.mShapes [ 0 ], t0, t1 );
			}
		}
		else {
		
			for ( size_t i = 0; i < shapeCount1; ++i ) {
				this->Process ( *shape0.mShapes [ 0 ], *shape1.mShapes [ i ], t0, t1 );
			}
		}
	}
	else {
	
		for ( size_t i = 0; i < shapeCount0; ++i ) {
			for ( size_t j = 0; j < shapeCount1; ++j ) {
				this->Process ( *shape0.mShapes [ i ], *shape1.mShapes [ j ], t0, t1 );
			}
		}
	}
}

//----------------------------------------------------------------//
void MOAICollisionPrimVisitor::SetProps ( MOAICollisionProp* prop0, MOAICollisionProp* prop1 ) {

	this->mProp0 = prop0;
	this->mProp1 = prop1;
}