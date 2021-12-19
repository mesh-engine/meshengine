/*************************************************************************/
/*  mesh_result_callbacks.cpp                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Mesh Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "mesh_result_callbacks.h"

#include "area_bullet.h"
#include "bullet_types_converter.h"
#include "collision_object_bullet.h"
#include "rigid_body_bullet.h"
#include <BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>

/**
	@author AndreaCatania
*/

bool meshContactAddedCallback(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1) {
	if (!colObj1Wrap->getCollisionObject()->getCollisionShape()->isCompound()) {
		btAdjustInternalEdgeContacts(cp, colObj1Wrap, colObj0Wrap, partId1, index1);
	}
	return true;
}

bool MeshFilterCallback::needBroadphaseCollision(btBroadphaseProxy *proxy0, btBroadphaseProxy *proxy1) const {
	return (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) || (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);
}

bool MeshClosestRayResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());

		if (CollisionObjectBullet::TYPE_AREA == gObj->getType()) {
			if (!collide_with_areas) {
				return false;
			}
		} else {
			if (!collide_with_bodies) {
				return false;
			}
		}

		if (m_pickRay && !gObj->is_ray_pickable()) {
			return false;
		}

		if (m_exclude->has(gObj->get_self())) {
			return false;
		}

		return true;
	} else {
		return false;
	}
}

bool MeshAllConvexResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (count >= m_resultMax) {
		return false;
	}

	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());
		if (m_exclude->has(gObj->get_self())) {
			return false;
		}

		return true;
	} else {
		return false;
	}
}

btScalar MeshAllConvexResultCallback::addSingleResult(btCollisionWorld::LocalConvexResult &convexResult, bool normalInWorldSpace) {
	if (count >= m_resultMax) {
		return 1; // not used by bullet
	}

	CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(convexResult.m_hitCollisionObject->getUserPointer());

	PhysicsDirectSpaceState3D::ShapeResult &result = m_results[count];

	// Triangle index is an odd name but contains the compound shape ID.
	// A shape part of -1 indicates the index is a shape index and not a triangle index.
	if (convexResult.m_localShapeInfo && convexResult.m_localShapeInfo->m_shapePart == -1) {
		result.shape = convexResult.m_localShapeInfo->m_triangleIndex;
	} else {
		result.shape = 0;
	}

	result.rid = gObj->get_self();
	result.collider_id = gObj->get_instance_id();
	result.collider = result.collider_id.is_null() ? nullptr : ObjectDB::get_instance(result.collider_id);

	++count;
	return 1; // not used by bullet
}

bool MeshKinClosestConvexResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());
		if (gObj == m_self_object) {
			return false;
		} else {
			// A kinematic body can't be stopped by a rigid body since the mass of kinematic body is infinite
			if (m_infinite_inertia && !btObj->isStaticOrKinematicObject()) {
				return false;
			}

			if (gObj->getType() == CollisionObjectBullet::TYPE_AREA) {
				return false;
			}

			if (m_self_object->has_collision_exception(gObj) || gObj->has_collision_exception(m_self_object)) {
				return false;
			}

			if (m_exclude->has(gObj->get_self())) {
				return false;
			}
		}
		return true;
	} else {
		return false;
	}
}

bool MeshClosestConvexResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());

		if (CollisionObjectBullet::TYPE_AREA == gObj->getType()) {
			if (!collide_with_areas) {
				return false;
			}
		} else {
			if (!collide_with_bodies) {
				return false;
			}
		}

		if (m_exclude->has(gObj->get_self())) {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

btScalar MeshClosestConvexResultCallback::addSingleResult(btCollisionWorld::LocalConvexResult &convexResult, bool normalInWorldSpace) {
	// Triangle index is an odd name but contains the compound shape ID.
	// A shape part of -1 indicates the index is a shape index and not a triangle index.
	if (convexResult.m_localShapeInfo && convexResult.m_localShapeInfo->m_shapePart == -1) {
		m_shapeId = convexResult.m_localShapeInfo->m_triangleIndex;
	} else {
		m_shapeId = 0;
	}

	return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
}

bool MeshAllContactResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (m_count >= m_resultMax) {
		return false;
	}

	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());

		if (CollisionObjectBullet::TYPE_AREA == gObj->getType()) {
			if (!collide_with_areas) {
				return false;
			}
		} else {
			if (!collide_with_bodies) {
				return false;
			}
		}

		if (m_exclude->has(gObj->get_self())) {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

btScalar MeshAllContactResultCallback::addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1) {
	if (m_count >= m_resultMax) {
		return cp.getDistance();
	}

	if (cp.getDistance() <= 0) {
		PhysicsDirectSpaceState3D::ShapeResult &result = m_results[m_count];
		// Penetrated

		CollisionObjectBullet *colObj;
		if (m_self_object == colObj0Wrap->getCollisionObject()) {
			colObj = static_cast<CollisionObjectBullet *>(colObj1Wrap->getCollisionObject()->getUserPointer());
			// Checking for compound shape because the index might be uninitialized otherwise.
			// A partId of -1 indicates the index is a shape index and not a triangle index.
			if (colObj1Wrap->getCollisionObject()->getCollisionShape()->isCompound() && cp.m_partId1 == -1) {
				result.shape = cp.m_index1;
			} else {
				result.shape = 0;
			}
		} else {
			colObj = static_cast<CollisionObjectBullet *>(colObj0Wrap->getCollisionObject()->getUserPointer());
			// Checking for compound shape because the index might be uninitialized otherwise.
			// A partId of -1 indicates the index is a shape index and not a triangle index.
			if (colObj0Wrap->getCollisionObject()->getCollisionShape()->isCompound() && cp.m_partId0 == -1) {
				result.shape = cp.m_index0;
			} else {
				result.shape = 0;
			}
		}

		result.collider_id = colObj->get_instance_id();
		result.collider = result.collider_id.is_null() ? nullptr : ObjectDB::get_instance(result.collider_id);
		result.rid = colObj->get_self();
		++m_count;
	}

	return cp.getDistance();
}

bool MeshContactPairContactResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (m_count >= m_resultMax) {
		return false;
	}

	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());

		if (CollisionObjectBullet::TYPE_AREA == gObj->getType()) {
			if (!collide_with_areas) {
				return false;
			}
		} else {
			if (!collide_with_bodies) {
				return false;
			}
		}

		if (m_exclude->has(gObj->get_self())) {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

btScalar MeshContactPairContactResultCallback::addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1) {
	if (m_count >= m_resultMax) {
		return 1; // not used by bullet
	}

	if (m_self_object == colObj0Wrap->getCollisionObject()) {
		B_TO_G(cp.m_localPointA, m_results[m_count * 2 + 0]); // Local contact
		B_TO_G(cp.m_localPointB, m_results[m_count * 2 + 1]);
	} else {
		B_TO_G(cp.m_localPointB, m_results[m_count * 2 + 0]); // Local contact
		B_TO_G(cp.m_localPointA, m_results[m_count * 2 + 1]);
	}

	++m_count;

	return 1; // Not used by bullet
}

bool MeshRestInfoContactResultCallback::needsCollision(btBroadphaseProxy *proxy0) const {
	if (proxy0->m_collisionFilterGroup & m_collisionFilterMask) {
		btCollisionObject *btObj = static_cast<btCollisionObject *>(proxy0->m_clientObject);
		CollisionObjectBullet *gObj = static_cast<CollisionObjectBullet *>(btObj->getUserPointer());

		if (CollisionObjectBullet::TYPE_AREA == gObj->getType()) {
			if (!collide_with_areas) {
				return false;
			}
		} else {
			if (!collide_with_bodies) {
				return false;
			}
		}

		if (m_exclude->has(gObj->get_self())) {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

btScalar MeshRestInfoContactResultCallback::addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1) {
	if (cp.getDistance() <= m_min_distance) {
		m_min_distance = cp.getDistance();

		CollisionObjectBullet *colObj;
		if (m_self_object == colObj0Wrap->getCollisionObject()) {
			colObj = static_cast<CollisionObjectBullet *>(colObj1Wrap->getCollisionObject()->getUserPointer());
			// Checking for compound shape because the index might be uninitialized otherwise.
			// A partId of -1 indicates the index is a shape index and not a triangle index.
			if (colObj1Wrap->getCollisionObject()->getCollisionShape()->isCompound() && cp.m_partId1 == -1) {
				m_result->shape = cp.m_index1;
			} else {
				m_result->shape = 0;
			}
			B_TO_G(cp.getPositionWorldOnB(), m_result->point);
			B_TO_G(cp.m_normalWorldOnB, m_result->normal);
			m_rest_info_bt_point = cp.getPositionWorldOnB();
			m_rest_info_collision_object = colObj1Wrap->getCollisionObject();
		} else {
			colObj = static_cast<CollisionObjectBullet *>(colObj0Wrap->getCollisionObject()->getUserPointer());
			// Checking for compound shape because the index might be uninitialized otherwise.
			// A partId of -1 indicates the index is a shape index and not a triangle index.
			if (colObj0Wrap->getCollisionObject()->getCollisionShape()->isCompound() && cp.m_partId0 == -1) {
				m_result->shape = cp.m_index0;
			} else {
				m_result->shape = 0;
			}
			B_TO_G(cp.m_normalWorldOnB * -1, m_result->normal);
			m_rest_info_bt_point = cp.getPositionWorldOnA();
			m_rest_info_collision_object = colObj0Wrap->getCollisionObject();
		}

		m_result->collider_id = colObj->get_instance_id();
		m_result->rid = colObj->get_self();

		m_collided = true;
	}

	return 1; // Not used by bullet
}

void MeshDeepPenetrationContactResultCallback::addContactPoint(const btVector3 &normalOnBInWorld, const btVector3 &pointInWorldOnB, btScalar depth) {
	if (m_penetration_distance > depth) { // Has penetration?

		const bool isSwapped = m_manifoldPtr->getBody0() != m_body0Wrap->getCollisionObject();
		m_penetration_distance = depth;
		m_other_compound_shape_index = isSwapped ? m_index0 : m_index1;
		m_pointWorld = isSwapped ? (pointInWorldOnB + (normalOnBInWorld * depth)) : pointInWorldOnB;

		m_pointNormalWorld = isSwapped ? normalOnBInWorld * -1 : normalOnBInWorld;
	}
}
