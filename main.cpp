#include <iostream>
#include <chrono>
#include <thread>
#include "btBulletDynamicsCommon.h"
#include "MyDebugDrawer.h"

#define BIT(x) (1<<(x))

enum CG {
    NOTHING = 0,
    MONSTER = BIT(1),
    PLAYER = BIT(2),
    SKILL = BIT(3)
};

btRigidBody *createRigidBody(const btVector3 &position) {
    btCollisionShape *shape = new btCylinderShape(btVector3(0.5, 0.5, 0.5));
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(position);
    auto *obj1MotionState = new btDefaultMotionState(trans);
    btRigidBody::btRigidBodyConstructionInfo obj1Construct(btScalar(1.f), obj1MotionState, shape);
    auto *body1 = new btRigidBody(obj1Construct);
    body1->setLinearVelocity(
            btVector3(1, 1, 0));
    btTransform centerTrans;
    centerTrans.setIdentity();
    centerTrans.setOrigin(btVector3(0, 0.5, 0));
    body1->setCenterOfMassTransform(centerTrans);
    
    return body1;
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);


    btCollisionConfiguration *configuration = new btDefaultCollisionConfiguration;
    btCollisionDispatcher *dispatcher = new btCollisionDispatcher(configuration);
    btBroadphaseInterface *overlappingcache = new btDbvtBroadphase;
    btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld *dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingcache, solver,
                                                                         configuration);
    dynamicsWorld->setGravity(btVector3(0, 0, 0));

    btVector3 position = {0, 0, 0};
    auto body1 = createRigidBody(position);
//    body1->setCollisionFlags(body1->getCollisionFlags()|btCollisionObject::CF_KINEMATIC_OBJECT);
//    body1->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(body1, CG::PLAYER, CG::MONSTER);
//    body1->setCollisionFlags(body1->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    body1->setCollisionFlags(body1->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

    btVector3 position2 = {5, 5, 0};
    auto body2 = createRigidBody(position2);
    body2->setLinearVelocity(btVector3(0, 0, 0));
    dynamicsWorld->addRigidBody(body2, CG::MONSTER, CG::PLAYER);

    auto num = 0;
    auto start_time = std::chrono::system_clock::now();
    for (int k = 0; k < 260; ++k) {
        dynamicsWorld->stepSimulation(1.0 / 60.0);

    }


    num = dynamicsWorld->getDispatcher()->getNumManifolds();
    std::cout << "num: " << num << std::endl;


    auto interval = std::chrono::system_clock::now() - start_time;
    std::cout << " time interval : " << std::chrono::duration_cast<std::chrono::milliseconds>(interval).count() << " ms"
              << std::endl;


    for (int i = 0; i < num; ++i) {
        auto *contact = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        auto *objA = contact->getBody0();
        auto *objB = contact->getBody1();

        int numContacts = contact->getNumContacts();
        for (int j = 0; j < numContacts; ++j) {
            auto &pt = contact->getContactPoint(j);
            if (pt.getDistance() < 0.f) {
                std::cout << pt.getPositionWorldOnA()
                          << pt.getPositionWorldOnB()
                          << pt.m_normalWorldOnB;
            }
        }
    }

    MyDebugDrawer *debugDrawer = new MyDebugDrawer;
    dynamicsWorld->setDebugDrawer(debugDrawer);
    dynamicsWorld->debugDrawWorld();
    return 0;
}