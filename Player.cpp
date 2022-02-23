#include "CPlayer.h"
#include <cmath>


const int WAY_POINT_RADIUS = 3.0f;

CPlayer::CPlayer(IMesh* npcMesh, float xCoordinate,float yCoordinate,float zCoordinate)
{
	m_npc = npcMesh->CreateModel(xCoordinate, yCoordinate, zCoordinate);
	m_npc->SetSkin("glass_blue.jpg");
	m_velocity = 0.0f;
	m_radius = 3.0f;
}

void CPlayer::SetVelocity(float startingVelocity, float dt)
{
	m_velocity = startingVelocity*dt;
}

void CPlayer::SetRadius(float radius) {
	m_radius = radius;
}

void CPlayer::Move()
{
	m_npc->MoveLocalZ(m_velocity);
}

void CPlayer::UpdateHover(IModel* wayPoints[],string &current_game_state,string &winner_hover) {
	Move();
	switch (m_state) {
		case FIRST_WAYPOINT:
			m_npc->LookAt(wayPoints[FIRST_WAYPOINT]);
			if (Collision(wayPoints, FIRST_WAYPOINT)) {
				m_state = SECOND_WAYPOINT;
				if (m_lap_state == 2) {
					m_game_state_int = FIRST_CHECKPOINT_LAP2;
				}
				else {
					m_game_state_int = FIRST_CHECKPOINT;

				}
			}
			break;
		case SECOND_WAYPOINT:
			m_npc->LookAt(wayPoints[SECOND_WAYPOINT]);
			if (Collision(wayPoints, SECOND_WAYPOINT)) {
				m_state = THIRD_WAYPOINT;
			}
			break;
		case THIRD_WAYPOINT://1ST CHECKPOINT
			m_npc->LookAt(wayPoints[THIRD_WAYPOINT]);
			if (Collision(wayPoints, THIRD_WAYPOINT)) {
				m_state = FOURTH_WAYPOINT;
				if (m_lap_state == 2) {
					m_game_state_int = SECOND_CHECKPOINT_LAP2;
				}
				else {
					m_game_state_int = SECOND_CHECKPOINT;

				}
			}
			break;
		case FOURTH_WAYPOINT:
			m_npc->LookAt(wayPoints[FOURTH_WAYPOINT]);
			if (Collision(wayPoints, FOURTH_WAYPOINT)) {
				m_state = FIFTH_WAYPOINT;
			}
			break;
		case FIFTH_WAYPOINT:
			m_npc->LookAt(wayPoints[FIFTH_WAYPOINT]);
			if (Collision(wayPoints, FIFTH_WAYPOINT)) {
				m_state = SIXTH_WAYPOINT;
			}
			break;
		case SIXTH_WAYPOINT://2ND CHECKPOINT
			m_npc->LookAt(wayPoints[SIXTH_WAYPOINT]);
			if (Collision(wayPoints, SIXTH_WAYPOINT)) {
				m_state = SEVENTH_WAYPOINT;
				if (m_lap_state == 2) {
					m_game_state_int = THIRD_CHECKPOINT_LAP2;
				}
				else {
					m_game_state_int = THIRD_CHECKPOINT;

				}
			}
			break;
		case SEVENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[SEVENTH_WAYPOINT]);
			if (Collision(wayPoints, SEVENTH_WAYPOINT)) {
				m_state = EIGHTH_WAYPOINT;
				m_game_state_int = THIRD_CHECKPOINT;
			}
			break;
		case EIGHTH_WAYPOINT://3RD CHECKPOINT
			m_npc->LookAt(wayPoints[EIGHTH_WAYPOINT]);
			if (Collision(wayPoints, EIGHTH_WAYPOINT)) {
				m_state = NINTH_WAYPOINT;
				m_game_state_int = FOURTH_CHECKPOINT;
			}
			break;
		case NINTH_WAYPOINT:
			m_npc->LookAt(wayPoints[NINTH_WAYPOINT]);
			if (Collision(wayPoints, NINTH_WAYPOINT)) {
				m_state = TENTH_WAYPOINT;
				if (m_lap_state == 2) {
					m_game_state_int = FOURTH_CHECKPOINT_LAP2;
				}
				else {
					m_game_state_int = FOURTH_CHECKPOINT;
				}
			}
			break;
		case TENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[TENTH_WAYPOINT]);
			if (Collision(wayPoints, TENTH_WAYPOINT)) {
				m_state = ELEVENTH_WAYPOINT;
			}
			break;
		case ELEVENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[ELEVENTH_WAYPOINT]);
			if (Collision(wayPoints, ELEVENTH_WAYPOINT)) {
				m_state = TWELFTH_WAYPOINT;
			}
			break;
		case TWELFTH_WAYPOINT://4TH CHECKPOINT
			m_npc->LookAt(wayPoints[TWELFTH_WAYPOINT]);
			if (Collision(wayPoints, TWELFTH_WAYPOINT)) {
				m_state = THIRTEENTH_WAYPOINT;
				m_game_state_int = FIFTH_CHECKPOINT;
			}
			break;
		case THIRTEENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[THIRTEENTH_WAYPOINT]);
			if (Collision(wayPoints, THIRTEENTH_WAYPOINT)) {
				m_state = FOURTEENTH_WAYPOINT;
				if (m_lap_state == 2) {
					m_game_state_int = FIFTH_CHECKPOINT_LAP2;
				}
				else {
					m_game_state_int = FIFTH_CHECKPOINT;
				}
			}
			break;
		case FOURTEENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[FOURTEENTH_WAYPOINT]);
			if (Collision(wayPoints, FOURTEENTH_WAYPOINT)) {
				m_state = FIFTEENTH_WAYPOINT;
			}
			break;
		case FIFTEENTH_WAYPOINT://5TH CHECKPOINT
			m_npc->LookAt(wayPoints[FIFTEENTH_WAYPOINT]);
			if (Collision(wayPoints, FIFTEENTH_WAYPOINT)) {
				m_state = SIXTEENTH_WAYPOINT;
				if (m_lap_state == 2) {
					m_game_state_int = LAST_CHECKPOINT_LAP2;
				}
				else {
					m_game_state_int = LAST_CHECKPOINT;
				}
			}
			break;
		case SIXTEENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[SIXTEENTH_WAYPOINT]);
			if (Collision(wayPoints, SIXTEENTH_WAYPOINT)) {
				m_state = SEVENTEENTH_WAYPOINT;
			}
			break;
		case SEVENTEENTH_WAYPOINT:
			m_npc->LookAt(wayPoints[SEVENTEENTH_WAYPOINT]);
			if (Collision(wayPoints, SEVENTEENTH_WAYPOINT)) {
				m_state = LAST_WAYPOINT;
			}
			break;
		case LAST_WAYPOINT://LAST CHECKPOINT
			m_npc->LookAt(wayPoints[LAST_WAYPOINT]);
			if (Collision(wayPoints, LAST_WAYPOINT)) {
				if (m_lap_state != 2) {
					m_state = FIRST_WAYPOINT;
					m_lap_state = 2;
				}
				else {
					current_game_state = OVER_STATE;
					winner_hover = "NPC";
				}	
			}
			break;
	}
	
	
}

bool CPlayer::Collision(IModel* wayPoints[], int index){

	double xCoordinates = m_npc->GetLocalX() - wayPoints[index]->GetLocalX();
	double yCoordinates = m_npc->GetLocalY() - wayPoints[index]->GetLocalY();
	double zCoordinates = m_npc->GetLocalZ() - wayPoints[index]->GetLocalZ();

	/*Calculate the distance from car to other object*/
	double distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
	/*Collision occurred*/
	/*front wing*/
	if (distance < m_radius + WAY_POINT_RADIUS) {
		return true;
	}
	return false;
}

CPlayer::~CPlayer()
{
}
