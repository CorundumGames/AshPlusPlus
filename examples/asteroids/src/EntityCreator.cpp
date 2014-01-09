#include "EntityCreator.hpp"

#include "ash/tools/ComponentPool.hpp"

#include "asteroids/include/components/components.hpp"

#include "asteroids/include/graphics/AsteroidView.hpp"
#include "asteroids/include/Util.hpp"

namespace net {
namespace richardlord {
namespace asteroids {

using namespace net::richardlord::asteroids::graphics;

void EntityCreator::destroyEntity(const shared_ptr<Entity> entity) {
    this->_engine->removeEntity(entity);
    if (entity->has<Asteroid>()) {
        ash::tools::ComponentPool<Asteroid>::dispose(entity->get<Asteroid>());
    }
}

shared_ptr<Entity> EntityCreator::createGame() {
    shared_ptr<Entity> entity(make_shared<Entity>());
    entity->add(make_shared<GameState>());
    this->_engine->addEntity(entity);
    return entity;
}

shared_ptr<Entity> EntityCreator::createAsteroid(
    const double radius, const double x, const double y) {
    shared_ptr<Entity> asteroid(make_shared<Entity>());
    asteroid->
    add<Asteroid>(make_shared<Asteroid>())
    .add<Position>(make_shared<Position>(x, y, 0))
    .add<Collision>(make_shared<Collision>(radius))
    .add<Motion>(make_shared<Motion>((random() - .5) * 4 * (50 - radius),
                                     (random() - .5) * 4 * (50 - radius), random() * 2 - 1, 0))
    .add<Display>(make_shared<Display>(make_shared<AsteroidView>(radius)));

    this->_engine->addEntity(asteroid);
    return asteroid;
    /*
    var asteroid:Entity = new Entity()
    .add(ComponentPool.get(Asteroid))
    .add(new Position( x, y, 0))
    .add(new Collision(radius))
    .add(new Motion( ( Math.random() - 0.5 ) * 4 * ( 50 - radius ), ( Math.random() - 0.5 ) * 4 * ( 50 - radius ), Math.random() * 2 - 1, 0 ))
    .add(new Display( new AsteroidView( radius ) ));
    engine.addEntity(asteroid);
    return asteroid;
    */

}

shared_ptr<Entity> EntityCreator::createSpaceship() {
    /*
    var spaceship : Entity = new Entity();
        var fsm : EntityStateMachine = new EntityStateMachine( spaceship );

        fsm.createState( "playing" )
        .add( Motion ).withInstance( new Motion( 0, 0, 0, 15 ) )
        .add( MotionControls ).withInstance( new MotionControls( Keyboard.LEFT, Keyboard.RIGHT, Keyboard.UP, 100, 3 ) )
        .add( Gun ).withInstance( new Gun( 8, 0, 0.3, 2 ) )
        .add( GunControls ).withInstance( new GunControls( Keyboard.SPACE ) )
        .add( Collision ).withInstance( new Collision( 9 ) )
        .add( Display ).withInstance( new Display( new SpaceshipView() ) );

        var deathView : SpaceshipDeathView = new SpaceshipDeathView();
        fsm.createState( "destroyed" )
        .add( DeathThroes ).withInstance( new DeathThroes( 5 ) )
        .add( Display ).withInstance( new Display( deathView ) )
        .add( Animation ).withInstance( new Animation( deathView ) );

        spaceship.add( new Spaceship( fsm ) ).add( new Position( 300, 225, 0 ) );

        fsm.changeState( "playing" );
        engine.addEntity(spaceship);

        return spaceship;
        */
}

shared_ptr<Entity> EntityCreator::createUserBullet(const Gun& gun, const Position& position) {
    /*
    var cos:Float = Math.cos(parentPosition.rotation);
    var sin:Float = Math.sin(parentPosition.rotation);
    var bullet:Entity = new Entity()
    .add(new Bullet( gun.bulletLifetime ))
    .add(new Position(
         cos * gun.offsetFromParent.x - sin * gun.offsetFromParent.y + parentPosition.position.x, sin * gun.offsetFromParent.x + cos * gun.offsetFromParent.y + parentPosition.position.y, 0))
    .add(new Collision(0))
    .add(new Motion( cos * 150, sin * 150, 0, 0 ))
    .add(new Display( new BulletView() ));
    engine.addEntity(bullet);
    return bullet;
    */

}

}
}
}
