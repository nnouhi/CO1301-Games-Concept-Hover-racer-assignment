#pragma once
#include <TL-Engine.h>
#include "Macros.h"

using namespace tle;

class CPlayer
{
private:
	//private members atributes
	IModel* m_npc;
	float m_velocity;
	float m_radius;
	int m_state = FIRST_WAYPOINT;
	int m_game_state_int = FIRST_CHECKPOINT;
	int m_lap_state=0;

	void Move();
	bool Collision(IModel* wayPoints[], int index);

public:
	CPlayer(IMesh* npcMesh, float xCoordinate, float yCoordinate, float zCoordinate);
	~CPlayer();

	// method that returns the model of the player
	IModel* GetModel() { return m_npc; }
	// method that returs the velocity of the player
	float GetVelocity() { return m_velocity; }

	float GetNpcRadius() { return m_radius; }

	int GetLapState() { return m_lap_state; }

	int GetGameState() { return m_game_state_int; }

	void SetVelocity(float startingVelocity, float dt);

	void SetRadius(float radius);


	void UpdateHover(IModel* wayPoints[], string &current_game_state,string &winner_hover);

};

