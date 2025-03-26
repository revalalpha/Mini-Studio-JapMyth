#include "Game.h"

#include "IGameObject.h"

#include "Barrier.h"
#include "Fireball.h"
#include "Inugami.h"
#include "Kappa.h"
#include "OrbitalProjectile.h"
#include "PlayerShip.h"
#include "Samurai.h"

#define HANDLE_COLLIDE(Type1, Type2, EnumType1, EnumType2, fn) \
if (go1->gameObjectType() == EnumType1 && go2->gameObjectType() == EnumType2)\
{\
    fn(static_cast<Type1*>(go1), static_cast<Type2*>(go2));\
}\
if (go1->gameObjectType() == EnumType2 && go2->gameObjectType() == EnumType1)\
{\
    fn(static_cast<Type1*>(go2), static_cast<Type2*>(go1));\
}


void collision_Barrier_Fireball(Barrier* go1, Fireball* go2)
{
    go2->destroy();
}


void collision_Barrier_PlayerShip(Barrier* go1, PlayerShip* go2)
{
    go2->destroy();
}
void collision_Ship_EnemyFireball(PlayerShip* go1, Fireball* go2)
{
    go1->takeDamage(1);
    go2->destroy();
}
void collision_Ship_EnemyMelee(PlayerShip* go1, OrbitalProjectile* go2)
{
    go1->takeDamage(1);
}
void collision_Barrier_Samurai(Barrier* go1, Samurai* go2)
{
    go2->destroy();
}

void collision_Samurai_PlayerProjectile(Samurai* go1, Fireball* go2)
{
    go1->takeDamage(1);
    go2->destroy();
}
void collision_Ship_Samurai(PlayerShip* go1, Samurai* go2)
{
    go1->takeDamage(1);
}
void collision_Samurai_ShipMelee(Samurai* go1, OrbitalProjectile* go2)
{
    go1->takeDamage(2);
}


void collision_Barrier_Kappa(Barrier* go1, Kappa* go2)
{
    go2->destroy();
}

void collision_Kappa_PlayerProjectile(Kappa* go1, Fireball* go2)
{
    go1->takeDamage(1);
    go2->destroy();
}
void collision_Ship_Kappa(PlayerShip* go1, Kappa* go2)
{
    go1->takeDamage(1);
}
void collision_Kappa_ShipMelee(Kappa* go1, OrbitalProjectile* go2)
{
    go1->takeDamage(2);
}

void collision_Barrier_Inugami(Barrier* go1, Inugami* go2)
{
    go2->destroy();
}

void collision_Inugami_PlayerProjectile(Inugami* go1, Fireball* go2)
{
    go1->takeDamage(1);
    go2->destroy();
}
void collision_Ship_Inugami(PlayerShip* go1, Inugami* go2)
{
    go1->takeDamage(1);
}
void collision_Inugami_ShipMelee(Inugami* go1, OrbitalProjectile* go2)
{
    go1->takeDamage(2);
}

void Game::onCollision(IGameObject* go1, IGameObject* go2)
{

    HANDLE_COLLIDE(Barrier, Fireball, BARRIER_TYPE, ENEMYprojectile_TYPE, collision_Barrier_Fireball)
	
	HANDLE_COLLIDE(Barrier, Fireball, BARRIER_TYPE, PLAYERprojectile_TYPE, collision_Barrier_Fireball)
    HANDLE_COLLIDE(Barrier, PlayerShip, BARRIER_TYPE, PLAYERSHIP_TYPE, collision_Barrier_PlayerShip)
	HANDLE_COLLIDE(PlayerShip, Fireball, PLAYERSHIP_TYPE, ENEMYprojectile_TYPE, collision_Ship_EnemyFireball)
	HANDLE_COLLIDE(PlayerShip, OrbitalProjectile, PLAYERSHIP_TYPE, ENEMYmelee_TYPE, collision_Ship_EnemyMelee)
	
	HANDLE_COLLIDE(PlayerShip, Samurai, PLAYERSHIP_TYPE, SAMURAI_TYPE, collision_Ship_Samurai)
	HANDLE_COLLIDE(Samurai, OrbitalProjectile, SAMURAI_TYPE, PLAYERmelee_TYPE, collision_Samurai_ShipMelee)
	HANDLE_COLLIDE(Samurai, Fireball, SAMURAI_TYPE, PLAYERprojectile_TYPE, collision_Samurai_PlayerProjectile)
	HANDLE_COLLIDE(Barrier, Samurai, BARRIER_TYPE, SAMURAI_TYPE, collision_Barrier_Samurai)

	HANDLE_COLLIDE(PlayerShip, Kappa, PLAYERSHIP_TYPE, KAPPA_TYPE, collision_Ship_Kappa)
	HANDLE_COLLIDE(Kappa, OrbitalProjectile, KAPPA_TYPE, PLAYERmelee_TYPE, collision_Kappa_ShipMelee)
	HANDLE_COLLIDE(Kappa, Fireball, KAPPA_TYPE, PLAYERprojectile_TYPE, collision_Kappa_PlayerProjectile)
	HANDLE_COLLIDE(Barrier, Kappa, BARRIER_TYPE, KAPPA_TYPE, collision_Barrier_Kappa)

	HANDLE_COLLIDE(PlayerShip, Inugami, PLAYERSHIP_TYPE, INUGAMI_TYPE, collision_Ship_Inugami)
	HANDLE_COLLIDE(Inugami, OrbitalProjectile, INUGAMI_TYPE, PLAYERmelee_TYPE, collision_Inugami_ShipMelee)
	HANDLE_COLLIDE(Inugami, Fireball, INUGAMI_TYPE, PLAYERprojectile_TYPE, collision_Inugami_PlayerProjectile)
	HANDLE_COLLIDE(Barrier, Inugami, BARRIER_TYPE, INUGAMI_TYPE, collision_Barrier_Inugami)
}
