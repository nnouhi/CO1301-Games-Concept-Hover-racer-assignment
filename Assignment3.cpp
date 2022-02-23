// Assignment3.cpp: A program using the TL-Engine
//Nicolas Nouhi
#include <TL-Engine.h>
#include <iostream>
#include <sstream>
#include <math.h> 
#include <ctime> 
#include "Macros.h"
#include "CPlayer.h"
using namespace tle;


/*******************************************CONSTANT VARIABLES USED START*******************************************/
/*radius constants used in game*/
const float cp_dummy_radius = 0.5f;
const float cp_radius = 3.0f;
const float CAR_RADIUS = 3.0f;
const float isleRadius = 3.0f;
const float ISLE_CORNER_RADIUS = 5.0f;
const float ISLE_CROSS_RADIUS = 5.0f;
const float SPEED_BOOST_RADIUS = 1.5f;
const float TRIBUNE_RADIUS = 8.0f;

/*Constant variables used for the camera*/
const float CAMERA_VELOCITY = 80.0f;
const float kCameraMovement = 100.0f;

/*Model array sizes*/
const int ISLE_SIZE = 10;
const int ISLE_SIZE2 = 15;
const int ISLE_CORNER_SIZE = 4;
const int CHECKPOINT_SIZE = 6;
const int WALL_SIZE_LEFT = 120; /*120 walls used for the left side of the piste*/
const int WALL_SIZE_RIGHT = 318; /*318 walls used for the right side* piste*/
const int WALL_SIZE = WALL_SIZE_LEFT + WALL_SIZE_RIGHT; /*get the total size of all wals use*/
const int TANK_SIZE = 12;
const int TRIBUNE_SIZE = 6;
const int CHECKPOINT_LEGS_SIZE = 12;
const int SPEEDBOOST_SIZE = 3;
const int WAY_POINTS_SIZE = 20;
const int LAP_SIZE = 2;


/*Constants used for the hover race car*/
const float kSteerLimit = 40.0f; // Limit on the angle of steering
const float kLeanLimit = 40.0f;
const float kSteerSpeed = 60.0f; // Steering speed of the hover
const float kPi = 3.1415f;
const float ACCEL_BW = 0.01f;
const float GRAVITY = 0.075f;
const float LIMIT_FLOAT_TOP = 1.0f;
const float LIMIT_FLOAT_BOTTOM = 0.5f;
const float OVERHEAT_LIMIT_SPEED = 50.f;
const float NPC_VELOCITY = 40.0f;
const float NPC_RADIUS = 3.0f;

/*Constants used for the fonts and srite*/
const float sprite_x = 750.0f;
const float sprite_y = 600.0f;
const float FONT_X = 500.0f;
const float FONT_Y = 300.0f;

const float font_x_cnt_down = 620.0f;
const float font_y_cnt_down = 400.0f;

const float FONT_X_CURRENT_GAME_STATE= 780.0f;
const float FONT_Y_CURRENT_GAME_STATE = 605.0f;

const float FONT_X_BOOST_STATE = 780.0f;
const float FONT_Y_BOOST_STATE = 630.0f;


const float FONT_X_CURRENT_VELOCITY = 1100.0f;
const float FONT_Y_CURRENT_VELOCITY = 630.0f;

const float LAP_X = 0.0f;
const float LAP_Y = 0.0f;

const float MouseRotation = 10.0f;
const float WheelMove = 10.0f; // distance for wheel movement z axis



/*Font variables*/
stringstream outText, test_text, current_game_state_text, boost_text, current_velocity, hover_hp, lap_text, show_position_text;

/*Global variables*/
float velocity = 0.0f, steering = 0.0f, velocityY = 0.0f, top_speed = 200.0f, top_speed_bw = -75.0f, friction = 0.025f, reduceVelocityBy = 0.0f;
int carHP = 100, currentLap = NO_LAP, npcCurrentLap = 1, cross_state = NO_CROSS, current_game_state_int, showRankingText = NPC_IS_FIRST;
float createCrossX = 0.0f, createCrossY = 0.0f, createCrossZ = 0.0f, crossYRotate = 0.0f;
bool overheat = false, hasCollided = false, hasCollidedOnce=false, front_side_hit = false, back_side_hit = false, power_state = OFF_POWER_BOOST;
time_t startBoost, endBoost, timeDiffBoost,startOverheat,endOverheat,timeDiffOverheat;//globals for the boost facility
time_t powerBoostTimeDiff, startPowerBoost, endPowerBoost;//globals for the speed package feature
time_t startCross, endCross, timeDiffCross;//globals for creating the cross model and deleting it
time_t startRace, endRace, timeDiffRace;//globals for showing the time that the first player took to complete the race

/*******************************************CONSTANT VARIABLES USED ENDS*******************************************/


/*******************************************LOAD MODELS FUNCTIONS START*******************************************/
/*Load checkpoint and cross models function*/
void load_checkpoint(IMesh* checkpointMesh, IModel* checkpointArr[]) {
	float checkpointXcoord = 0.0f, checkpointYcoord = 0.0f, checkpointZcoord = 0.0f, checkpointRotY = 0.0f, crossYcoord = 7.5f;
	float crossScaleDown = 0.25f;
	for (int i = 0; i < CHECKPOINT_SIZE; i++) {
		switch (i) {
			case FIRST_CHECKPOINT:
				checkpointXcoord = 0.0f;
				checkpointYcoord = 0.0f;
				checkpointZcoord = 20.0f;
				checkpointArr[i] = checkpointMesh->CreateModel(checkpointXcoord, checkpointYcoord, checkpointZcoord);
				break;
			case SECOND_CHECKPOINT:
				checkpointXcoord = -10.0f;
				checkpointYcoord = 0.0f;
				checkpointZcoord = 250.0f;
				checkpointRotY = -30.0f;
				checkpointArr[i] = checkpointMesh->CreateModel(checkpointXcoord, checkpointYcoord, checkpointZcoord);
				checkpointArr[i]->RotateLocalY(checkpointRotY);
				break;
			case THIRD_CHECKPOINT:
				checkpointXcoord = -180.0f;
				checkpointYcoord = 0.0f;
				checkpointZcoord = 280.0f;
				checkpointRotY = 90.0f;
				checkpointArr[i] = checkpointMesh->CreateModel(checkpointXcoord, checkpointYcoord, checkpointZcoord);
				checkpointArr[i]->RotateLocalY(checkpointRotY);
				break;
			case FOURTH_CHECKPOINT:
				checkpointXcoord = -330.0f;
				checkpointYcoord = 0.0f;
				checkpointZcoord = 250.0f;
				checkpointRotY = 30.0f;
				checkpointArr[i] = checkpointMesh->CreateModel(checkpointXcoord, checkpointYcoord, checkpointZcoord);
				checkpointArr[i]->RotateLocalY(checkpointRotY);
				break;
			case FIFTH_CHECKPOINT:
				checkpointXcoord = -360.0f;
				checkpointYcoord = 0.0f;
				checkpointZcoord = 20.0f;
				checkpointArr[i] = checkpointMesh->CreateModel(checkpointXcoord, checkpointYcoord, checkpointZcoord);
				break;
			case LAST_CHECKPOINT:
				checkpointXcoord = -180.0f;
				checkpointYcoord = 0.0f;
				checkpointZcoord = -80.0f;
				checkpointRotY = 90.0f;
				checkpointArr[i] = checkpointMesh->CreateModel(checkpointXcoord, checkpointYcoord, checkpointZcoord);

				checkpointArr[i]->RotateLocalY(checkpointRotY);
				break;
		}	
	}
}

/*Load left walls function*/
void load_walls_left(IMesh* wallMesh, IModel* wallArr[]) {
	/*Variables used to create the object in certain location*/
	float wallXcoord = -40.0f, wallZcoord = -30, wallYcoord = 0.0f, wallLength = 9.0f, wallAlign = 4.5f, wallRotY = 90.0f;
	/*Construct the left wall(inner square)*/
	for (int i = 0; i < WALL_SIZE_LEFT; i++) {
		/*Create 30 walls going straight*/
		if (i < FIRST_LINE_LIMIT) {
			wallArr[i] = wallMesh->CreateModel(wallXcoord, wallYcoord, wallZcoord);
			wallZcoord += wallLength;
		}
		/*create 30 walls going left and rotate them*/
		else if (i < SECOND_LINE_LIMIT) {
			/*subtract 4.5 from x and z to connect the last wall that was
			created above with the first one to be created right now */
			wallArr[i] = wallMesh->CreateModel(wallXcoord - wallAlign, wallYcoord, wallZcoord - wallAlign);
			wallArr[i]->RotateLocalY(wallRotY);
			wallXcoord -= wallLength;
		}
		/*Create 30 walls going backwards*/
		else if (i < THIRD_LINE_LIMIT) {
			/*substract 9 from the z to connect the last wall that was 
			created above with the first one to be created right now*/
			wallArr[i] = wallMesh->CreateModel(wallXcoord, wallYcoord, wallZcoord - wallLength);
			wallZcoord -= wallLength;
		}
		/*create 30 walls going right to connect with the first 30 walls created*/
		/*add 4.5 to x and substruct 4.5 from z to connect the last wall that was
		created above with the first one to be created right now */
		else if (i < FOURTH_LINE_LIMIT) {
			wallArr[i] = wallMesh->CreateModel(wallXcoord + wallAlign, wallYcoord, wallZcoord - wallAlign);
			wallArr[i]->RotateLocalY(wallRotY);
			wallXcoord += wallLength;
		}
	}
}

/*Load right walls function*/
void load_walls_right(IMesh* wallMesh, IModel* wallArr[]) {
	/*Variables used to create the object in certain location*/
	float wallXcoord = 40.0f, wallZcoord = -30, wallYcoord = 0.0f, wallLength = 9.0f, wallAlign = 4.5f, wallRotY = 90.0f;
	/*start creating right walls(outter square)*/
	for (int i = WALL_SIZE_LEFT; i < WALL_SIZE_RIGHT; i++) {
		/*Create 40 walls going straight*/
		if (i < FIRST_OUTTERLINE_LIMIT) {
			wallArr[i] = wallMesh->CreateModel(wallXcoord, wallYcoord, wallZcoord);
			wallZcoord += wallLength;
		}
		/*Create 49 walls going left and rotate them*/
		else if (i < SECOND_OUTTERLINE_LIMIT) {
			wallArr[i] = wallMesh->CreateModel(wallXcoord - wallAlign, wallYcoord, wallZcoord - wallAlign);
			wallArr[i]->RotateLocalY(wallRotY);
			wallXcoord -= wallLength;
		}
		/*create 49 walls going backwards*/
		else if (i < THIRD_OUTTERLINE_LIMIT) {
			wallArr[i] = wallMesh->CreateModel(wallXcoord, wallYcoord, wallZcoord - wallLength);
			wallZcoord -= wallLength;
		}
		/*create 49 walls going right*/
		else if (i < FOURTH_OUTTERLINE_LIMIT) {
			wallArr[i] = wallMesh->CreateModel(wallXcoord + wallAlign, wallYcoord, wallZcoord - wallAlign);
			wallArr[i]->RotateLocalY(wallRotY);
			wallXcoord += wallLength;
		}
		
		else {
			wallArr[i] = wallMesh->CreateModel(wallXcoord, wallYcoord, wallZcoord);
			wallZcoord += wallLength;
		}
		
	}
}

/**Load isles functions**/
/*Isle straight && Isle cross*/
void load_isles(IMesh* isle_straight_Mesh, IModel* isleStraightArr[],IMesh* isle_cross_Mesh, IModel* isleCrossArr[]) {
	/*Variables used to create the object in certain location(corridor)*/
	float z_left_side_corridor = 245.0f, z_right_side_corridor = 295.0f, x_corridor = -180, y_corridor = 0.0f, distance = 10.0f;

	/*Variables used to create the object in certain location(random isles positioned at the map)*/
	float z_random_isle = 75.0f, x_random_isle = -30.0f, y_random_isle = 0.0f, rot_random_Y = 90, distance_random = 20;
	
	/*Creates and positions the straight isle model to act as a close corridor*/
	for (int i = 0; i < ISLE_SIZE; i++) {
		if (i < LEFT_CORRIDOR_LIMIT) {
			isleStraightArr[i] = isle_straight_Mesh->CreateModel(x_corridor, y_corridor, z_left_side_corridor);
			z_left_side_corridor += distance;
		}
		else if(i < RIGHT_CORRIDOR_LIMIT){
			isleStraightArr[i] = isle_straight_Mesh->CreateModel(x_corridor, y_corridor, z_right_side_corridor);
			z_right_side_corridor += distance;
		}
		/*Place the other isles in 'random' locations*/
		else {
			isleStraightArr[i] = isle_straight_Mesh->CreateModel(x_random_isle, y_random_isle, z_random_isle);
			isleStraightArr[i]->RotateLocalY(rot_random_Y);
			x_random_isle += distance_random;
		}
	}


	float z_cross_coord = 0.0f,y_cross_coord = 0.0f , x_cross_coord = 0.0f;
	/*Creates and position the cross isle model in 'random' locations*/
	for(int i = 0; i < ISLE_SIZE2; i++) {
		switch (i) {
			case FIRST_CROSS_ISLE:
				z_cross_coord = 290.0f;
				x_cross_coord = -75.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case SECOND_CROSS_ISLE:
				z_cross_coord = 265.0f;
				x_cross_coord = -50.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case THIRD_CROSS_ISLE:
				z_cross_coord = 265.0f;
				x_cross_coord = -250.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case FOURTH_CROSS_ISLE:
				z_cross_coord = 280.0f;
				x_cross_coord = -280.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case FIFTH_CROSS_ISLE:
				z_cross_coord = 295.0f;
				x_cross_coord = -310.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case SIXTH_CROSS_ISLE:
				z_cross_coord = 150.0f;
				x_cross_coord = -325.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case SEVENTH_CROSS_ISLE:
				z_cross_coord = 150.0f;
				x_cross_coord = -350.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case EIGHTH_CROSS_ISLE:
				z_cross_coord = 50.0f;
				x_cross_coord = -350.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case NINTH_CROSS_ISLE:
				z_cross_coord = -60.0f;
				x_cross_coord = -345.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case TENTH_CROSS_ISLE:
				z_cross_coord = -60.0f;
				x_cross_coord = -375.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case ELEVENTH_CROSS_ISLE:
				z_cross_coord = -50.0f;
				x_cross_coord = -50.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case TWELFTH_CROSS_ISLE:
				z_cross_coord = -90.0f;
				x_cross_coord = -75.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case THIRDTEENTH_CROSS_ISLE:
				z_cross_coord = -110.0f;
				x_cross_coord = -75.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case FOURTEENTH_CROSS_ISLE:
				z_cross_coord = -100.0f;
				x_cross_coord = -150.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
			case FIFTHEEN_CROSS_ISLE:
				z_cross_coord = -70.0f;
				x_cross_coord = -150.0f;
				isleCrossArr[i] = isle_cross_Mesh->CreateModel(x_cross_coord, y_cross_coord, z_cross_coord);
				break;
		}			
	}
}
/*Isle corner*/
void load_isles_corner(IMesh* isle_corner_Mesh, IModel* isleCornerArr[]) {
	float isleXcoord = 0.0f, isleYcoord = 0.0f, isleZcoord = 0.0f, isleRotY=0.0f;
	
	for (int i = 0; i < ISLE_CORNER_SIZE; i++) {
		switch (i) {
			case FIRST_TURN_ISLE:
				isleXcoord = -37.0f;
				isleYcoord = 0.0f;
				isleZcoord = 238.0f;
				isleRotY = -180.0f;
				isleCornerArr[FIRST_TURN_ISLE] = isle_corner_Mesh->CreateModel(isleXcoord, isleYcoord, isleZcoord);
				isleCornerArr[FIRST_TURN_ISLE]->RotateLocalY(isleRotY);
				break;
			case SECOND_TURN_ISLE:
				isleXcoord = -313.0f;
				isleYcoord = 0.0f;
				isleZcoord = 238.0f;
				isleRotY = -280.0f;
				isleCornerArr[SECOND_TURN_ISLE] = isle_corner_Mesh->CreateModel(isleXcoord, isleYcoord, isleZcoord);
				isleCornerArr[SECOND_TURN_ISLE]->RotateLocalY(isleRotY);
				break;
			case THIRD_TURN_ISLE:
				isleXcoord = -313.0f;
				isleYcoord = 0.0f;
				isleZcoord = -37.0f;
				isleCornerArr[THIRD_TURN_ISLE] = isle_corner_Mesh->CreateModel(isleXcoord, isleYcoord, isleZcoord);
				break;
			case FOURTH_TURN_ISLE:
				isleXcoord = -37.0f;
				isleYcoord = 0.0f;
				isleZcoord = -37.0f;
				isleRotY = -90.0f;
				isleCornerArr[FOURTH_TURN_ISLE] = isle_corner_Mesh->CreateModel(isleXcoord, isleYcoord, isleZcoord);
				isleCornerArr[FOURTH_TURN_ISLE]->RotateLocalY(isleRotY);
				break;

		}
	}
}

/*Load tribune object function*/
void load_tribune(IMesh* tribuneMesh, IModel* tribuneArr[]) {
	/*Variables used to create the object in certain location*/
	float tribuneXcoord = 0.0f, tribuneYcoord = 0.0f, tribuneZcoord = 0.0f;
	for (int i = 0; i < TRIBUNE_SIZE; i++) {
		switch (i) {
			/*tribune down to the right*/
			case FIRST_TRIBUNE:
				tribuneXcoord = -45.0f;
				tribuneZcoord = -30.0f;
				tribuneArr[FIRST_TRIBUNE] = tribuneMesh->CreateModel(tribuneXcoord, tribuneYcoord, tribuneZcoord);
				tribuneArr[FIRST_TRIBUNE]->SetSkin("glass_blue.jpg");
				break;

			/*tribune down to the left*/
			case SECOND_TRIBUNE:
				tribuneXcoord = -305.0f;
				tribuneZcoord = -30.0f;
				tribuneArr[SECOND_TRIBUNE] = tribuneMesh->CreateModel(tribuneXcoord, tribuneYcoord, tribuneZcoord);
				tribuneArr[SECOND_TRIBUNE]->SetSkin("glass_red.jpg");
				break;

			/*tribune up to the left*/
			case THIRD_TRIBUNE:
				tribuneXcoord = -305.0f;
				tribuneZcoord = 230.0f;
				tribuneArr[THIRD_TRIBUNE] = tribuneMesh->CreateModel(tribuneXcoord, tribuneYcoord, tribuneZcoord);
				tribuneArr[THIRD_TRIBUNE]->SetSkin("glass_blue.jpg");

				break;
			/*tribune up to right*/
			case FOURTH_TRIBUNE:
				tribuneXcoord = -45.0f;
				tribuneZcoord = 230.0f;
				tribuneArr[FOURTH_TRIBUNE] = tribuneMesh->CreateModel(tribuneXcoord, tribuneYcoord, tribuneZcoord);
				tribuneArr[FOURTH_TRIBUNE]->SetSkin("glass_red.jpg");
				break;
		}
	}
}

/*Load water tanks function*/
void load_water_tanks(IMesh* tankMesh, IModel* tankArr[],double tank_z_min[], double tank_z_max[], double tank_y_min[], double tank_y_max[], double tank_x_min[], double tank_x_max[]) {
	/*Variables used to create the object in certain location*/
	float waterT_x_coord = 0.0f, waterT_y_coord = 0.0f, waterT_z_coord = 0.0f, waterT_rotate = 0.0f;
	
	/*Variables used for the Axis-Aligned Bounding Boxes*/
	float z_min = 0.0f, z_max = 0.0f, x_min = 0.0f, x_max = 0.0f, y_min = 0.0f, y_max = 0.0f;

	for (int i = 0; i < TANK_SIZE; i++) {
		switch (i) {
			/*case 0 and 1 are the half-buried in the sand and leaning at an angle water tanks*/
			case FIRST_WATER_TANK:
				waterT_x_coord = -5.0f;
				waterT_z_coord = 200.0f;
				waterT_y_coord = -5.0f;
				waterT_rotate = 50.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);
				tankArr[i]->RotateLocalX(waterT_rotate);

				z_max = 12.5f;
				z_min = 2.5f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() + z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case SECOND_WATER_TANK:
				waterT_x_coord = -200.0f;
				waterT_z_coord = 280.0f;
				waterT_y_coord = -5.0f;
				waterT_rotate = 50.0f;
		
				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);
				tankArr[i]->RotateLocalX(waterT_rotate);

				z_max = 12.5f;
				z_min = 5.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() + z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case THIRD_WATER_TANK:
				waterT_x_coord = -350.0f;
				waterT_z_coord = 100.0f;
				waterT_y_coord = -5.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 10.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case FOURTH_WATER_TANK:
				waterT_x_coord = -370.0f;
				waterT_z_coord = 80.0f;
				waterT_y_coord = 0.0f;
			
				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case FIFTH_WATER_TANK:
				waterT_x_coord = -330.0f;
				waterT_z_coord = -49.0f;
				waterT_y_coord = 0.0f;
	
				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);
				
				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case SIXTH_WATER_TANK:
				waterT_x_coord = -200.0f;
				waterT_z_coord = -100.0f;
				waterT_y_coord = -5.0f;
				waterT_rotate = -50.0f;
				
				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);
				tankArr[i]->RotateLocalZ(waterT_rotate);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 12.5f;
				y_min = 0.0f;
				x_max = 20.0f;
				x_min = 0.0f;
				
				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case PISTE_WATER_TANK_LEFT1:
				waterT_x_coord = 35.0f;
				waterT_z_coord = 20.0f;
				waterT_y_coord = 0.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case PISTE_WATER_TANK_LEFT2:
				waterT_x_coord = 25.0f;
				waterT_z_coord = 20.0f;
				waterT_y_coord = -10.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case PISTE_WATER_TANK_LEFT3:
				waterT_x_coord = 15.0f;
				waterT_z_coord = 20.0f;
				waterT_y_coord = 0.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case PISTE_WATER_TANK_RIGHT1:
				waterT_x_coord = -35.0f;
				waterT_z_coord = 20.0f;
				waterT_y_coord = 0.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case PISTE_WATER_TANK_RIGHT2:
				waterT_x_coord = -25.0f;
				waterT_z_coord = 20.0f;
				waterT_y_coord = -10.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
			case PISTE_WATER_TANK_RIGHT3:
				waterT_x_coord = -15.0f;
				waterT_z_coord = 20.0f;
				waterT_y_coord = 0.0f;

				tankArr[i] = tankMesh->CreateModel(waterT_x_coord, waterT_y_coord, waterT_z_coord);

				z_max = 2.0f;
				z_min = 2.0f;
				y_max = 15.0f;
				y_min = 0.0f;
				x_max = 2.0f;
				x_min = 2.0f;

				tank_z_max[i] = tankArr[i]->GetLocalZ() + z_max;
				tank_z_min[i] = tankArr[i]->GetLocalZ() - z_min;
				tank_y_min[i] = tankArr[i]->GetLocalY() - y_min;
				tank_y_max[i] = tankArr[i]->GetLocalY() + y_max;
				tank_x_min[i] = tankArr[i]->GetLocalX() - x_min;
				tank_x_max[i] = tankArr[i]->GetLocalX() + x_max;
				break;
		}
	}
}

/*Load dummy models for checkpoints' legs collision*/
void load_cpoints_dummies(IMesh* dummyMesh, IModel* cp_dummyArr[]) {
	/*Variables used to create the object in certain location*/
	float checkpoint_leg_xCoord = 0.0f, checkpoint_leg_yCoord = 0.0f, checkpoint_leg_zCoord = 0.0f;
	for (int i = 0; i < CHECKPOINT_LEGS_SIZE; i++) {
		switch (i) {
			case FIRST_CHECKPOINT_LEFT:
				checkpoint_leg_xCoord = -8.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 20.0f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case FIRST_CHECKPOINT_RIGHT:
				checkpoint_leg_xCoord = 8.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 20.0f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case SECOND_CHECKPOINT_LEFT:
				checkpoint_leg_xCoord = -2.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 254.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case SECOND_CHECKPOINT_RIGHT:
				checkpoint_leg_xCoord = -17.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 245.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case THIRD_CHECKPOINT_LEFT:
				checkpoint_leg_xCoord = -180.0f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 288.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case THIRD_CHECKPOINT_RIGHT:
				checkpoint_leg_xCoord = -180.0f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 271.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case FOURTH_CHECKPOINT_LEFT:
				checkpoint_leg_xCoord = -337.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 254.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			case FOURTH_CHECKPOINT_RIGHT:
				checkpoint_leg_xCoord = -322.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 245.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			/*5th checkpoint right leg dummy*/
			case FIFTH_CHECKPOINT_LEFT:
				checkpoint_leg_xCoord = -368.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 20.0f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			/*5rd checkpoint left leg dummy*/
			case FIFTH_CHECKPOINT_RIGHT:
				checkpoint_leg_xCoord = -351.5f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = 20.0f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			/*6th checkpoint right leg dummy*/
			case LAST_CHECKPOINT_LEFT:
				checkpoint_leg_xCoord = -180.0f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = -88.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
			/*6th checkpoint left leg dummy*/
			case LAST_CHECKPOINT_RIGHT:
				checkpoint_leg_xCoord = -180.0f;
				checkpoint_leg_yCoord = 0.0f;
				checkpoint_leg_zCoord = -71.5f;
				cp_dummyArr[i] = dummyMesh->CreateModel(checkpoint_leg_xCoord, checkpoint_leg_yCoord, checkpoint_leg_zCoord);
				break;
		}
	}
}

/*Get coordinates of all the walls in the game function*/
void get_coord_walls(IMesh* wallMesh, IModel* wallArr[], double wall_z_min[], double wall_z_max[], double wall_y_min[], double wall_y_max[], 
	double wall_x_min[], double wall_x_max[]) {
	float wall_width = 1.0f, wall_length = 5.0f, wall_height = 2.5f;
	/*Get the coordinates of all the left side walls
	  and store them */
	for (int i = 0; i < WALL_SIZE_LEFT; i++) {
		/*🡩  direction of left wall */
		if (i < FIRST_LINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_length;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_length;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_width;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_width;
		}
		/*🡨 wall is rotated change the wall width with wall length and vice versa*/
		else if (i < SECOND_LINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_width;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_width;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_length;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_length;
		}
		/*🡫*/
		else if (i < THIRD_LINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_length;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_length;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_width;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_width;
		}
		/*🡪 wall is rotated change the wall width with the wall length and vice versa*/
		else if(i < FOURTH_LINE_LIMIT){
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_width;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_width;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_length;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_length;
		}
	}

	/*Get the coordinates of all the right side wall
	  and store them in the array*/
	for (int i = WALL_SIZE_LEFT; i < WALL_SIZE_RIGHT; i++) {
		/*🡩  direction of right wall */
		if (i < FIRST_OUTTERLINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_length;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_length;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_width;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_width;
		}
		/*🡨 wall is rotated change the wall width with wall length and vice versa*/
		else if (i < SECOND_OUTTERLINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_width;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_width;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_length;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_length;
		}
		/*🡫*/
		else if (i < THIRD_OUTTERLINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_length;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_length;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_width;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_width;
		}
		/*🡪 wall is rotated change the wall width with the wall length and vice versa*/
		else if (i < FOURTH_OUTTERLINE_LIMIT) {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_width;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_width;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_length;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_length;
		}
		/*🡩 continue till straight line walls are filled out */
		else {
			wall_z_min[i] = wallArr[i]->GetLocalZ() - wall_length;
			wall_z_max[i] = wallArr[i]->GetLocalZ() + wall_length;
			wall_y_min[i] = wallArr[i]->GetLocalY() - wall_height;
			wall_y_max[i] = wallArr[i]->GetLocalY() + wall_height;
			wall_x_min[i] = wallArr[i]->GetLocalX() - wall_width;
			wall_x_max[i] = wallArr[i]->GetLocalX() + wall_width;
		}

	}


}

/*Load the waypoint dummies for the npc*/
void load_waypoints(IMesh* dummyMesh, IModel* wayPointsArr[]) {
	float wayPointXcoordinate = 0.0f, wayPointYcoordinate = 0.0f, wayPointZcoordinate = 0.0f;
	for (int i = 0; i < WAY_POINTS_SIZE; i++) {
		switch (i) {
			case FIRST_WAYPOINT:
				wayPointXcoordinate = 0.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 30.0f;
				wayPointsArr[i]=dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case SECOND_WAYPOINT:
				wayPointXcoordinate = 10.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 200.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case THIRD_WAYPOINT://1ST CHECKPOINT
				wayPointXcoordinate = -10.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 250.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case FOURTH_WAYPOINT:
				wayPointXcoordinate = -59.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 305.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case FIFTH_WAYPOINT:
				wayPointXcoordinate = -80.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 305.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case SIXTH_WAYPOINT://2ND CHECKPOINT
				wayPointXcoordinate = -180.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 280.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case SEVENTH_WAYPOINT:
				wayPointXcoordinate = -252.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 276.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case EIGHTH_WAYPOINT://3RD CHECKPOINT
				wayPointXcoordinate = -330.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 250.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case NINTH_WAYPOINT:
				wayPointXcoordinate = -360.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 218.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case TENTH_WAYPOINT:
				wayPointXcoordinate = -365.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 136.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case ELEVENTH_WAYPOINT:
				wayPointXcoordinate = -357.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 75.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case TWELFTH_WAYPOINT://4TH CHECKPOINT
				wayPointXcoordinate = -358.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 20.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case THIRTEENTH_WAYPOINT:
				wayPointXcoordinate = -320.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = -49.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case FOURTEENTH_WAYPOINT:
				wayPointXcoordinate = -263.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = -79.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case FIFTEENTH_WAYPOINT://5TH CHECKPOINT
				wayPointXcoordinate = -173.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = -79.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case SIXTEENTH_WAYPOINT:
				wayPointXcoordinate = -50.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = -100.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case SEVENTEENTH_WAYPOINT:
				wayPointXcoordinate = 0.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = -57.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
			case LAST_WAYPOINT://LAST CHECKPOINT
				wayPointXcoordinate = 0.0f;
				wayPointYcoordinate = 0.0f;
				wayPointZcoordinate = 20.0f;
				wayPointsArr[i] = dummyMesh->CreateModel(wayPointXcoordinate, wayPointYcoordinate, wayPointZcoordinate);
				break;
		}
	}
}


/*******************************************LOAD MODELS FUNCTIONS END*******************************************/

/*******************************************COLLISION FUNCTIONS START*******************************************/
/*sphere to box collision function*/
bool sphere_to_box(IModel* dummy, double object_z_min[], double object_z_max[], double object_y_min[],double object_y_max[],
	double object_x_min[], double object_x_max[]){
	for (int i = 0; i < WALL_SIZE; i++) {
		double dummyX = dummy->GetX();
		double dummyY = dummy->GetY();
		double dummyZ = dummy->GetZ();
		/*collision occurred*/
		if ((dummyX < object_x_max[i] + CAR_RADIUS) && (dummyX > object_x_min[i] - CAR_RADIUS) && (dummyY < object_y_max[i] + CAR_RADIUS) && (dummyY > object_y_min[i] - CAR_RADIUS) &&
			(dummyZ < object_z_max[i] + CAR_RADIUS) && (dummyZ > object_z_min[i] - CAR_RADIUS)) {
			return true;
		}
	}
	/*no collision*/
	return false;
}

/*sphere to sphere collision function (car collision with checkpoint and update current game state)*/
void sphere_to_sphere_cp(IModel* car, IModel* checkpointArr[], string &current_game_state, IFont* myFont, bool check_skipped_cp[],string &winner_hover) {
	double xCoordinates, yCoordinates, zCoordinates, distance;
	int timeToWait = 2;
	for (int i = 0; i < CHECKPOINT_LEGS_SIZE; i++) {
		switch (i) {
		case FIRST_CHECKPOINT:
			xCoordinates = car->GetLocalX() - checkpointArr[i]->GetLocalX();
			yCoordinates = car->GetLocalY() - checkpointArr[i]->GetLocalY();
			zCoordinates = car->GetLocalZ() - checkpointArr[i]->GetLocalZ();
			/*calculate distance*/
			distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			
			/*collision occurred*/
			if (distance < CAR_RADIUS + cp_radius) {
				if (check_skipped_cp[LAST_CHECKPOINT] == 1) {//if player passed the last checkpoint that means we are on second lap
					if (!hasCollidedOnce) {//check only once the lap
						if (currentLap == NO_LAP) {
							currentLap = LAP_1;
							hasCollidedOnce = true;
						}
						else if (currentLap == LAP_1) {
							currentLap = LAP_2;
							hasCollidedOnce = true;
						}
					}
					/*Reset all checkpoints to start the new lap*/
					for (int i = 0; i < CHECKPOINT_SIZE; i++) {
						check_skipped_cp[i] = 0; //reset all checkpoints
					}
					/*If we are on the last lap and the player cross the checkpoint end game*/
				}
				current_game_state = STAGE_1_COMPLETE_STATE;
				check_skipped_cp[FIRST_CHECKPOINT] = 1; // mark the first checkpoint as completed
				createCrossX = checkpointArr[i]->GetLocalX();
				createCrossY = checkpointArr[i]->GetLocalY();
				createCrossZ = checkpointArr[i]->GetLocalZ();
				if (cross_state == NO_CROSS) {//Create the cross model 
					cross_state = CREATE_CROSS;
				}
				if (currentLap == LAP_1) {
					current_game_state_int = FIRST_CHECKPOINT_LAP2;
				}
				else {
					current_game_state_int = FIRST_CHECKPOINT;
				}
				if (currentLap == LAP_2) {
					current_game_state = OVER_STATE;
					winner_hover = "You!";
				}
			
			}
			break;
		case SECOND_CHECKPOINT:
			xCoordinates = car->GetLocalX() - checkpointArr[i]->GetLocalX();
			yCoordinates = car->GetLocalY() - checkpointArr[i]->GetLocalY();
			zCoordinates = car->GetLocalZ() - checkpointArr[i]->GetLocalZ();
			/*calculate distance*/
			distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			/*collision occurred*/
			if (distance < CAR_RADIUS + cp_radius) {
				if (check_skipped_cp[i-1] == 1) { //and if checkpoint 1 was completed then change the game state
					if (currentLap == LAP_1) {
						current_game_state_int = SECOND_CHECKPOINT_LAP2;
					}
					else {
						current_game_state_int = SECOND_CHECKPOINT;
					}
					current_game_state = STAGE_2_COMPLETE_STATE;
					check_skipped_cp[i] = 1;
					/*If checkpoint was sucessfully passed store its position to spawn the cross*/
					createCrossX = checkpointArr[i]->GetLocalX();
					createCrossY = checkpointArr[i]->GetLocalY();
					createCrossZ = checkpointArr[i]->GetLocalZ();
					crossYRotate = -30.0f;
					if (cross_state == NO_CROSS) {//Create the cross model 
						cross_state = CREATE_CROSS;
					}
				}
				else {
					outText << "Checkpoint "<<i<<" Missed!" << endl;
					myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
					outText.str(""); // Clear myStream
				}
				
			}
			break;
		case THIRD_CHECKPOINT:
			xCoordinates = car->GetLocalX() - checkpointArr[i]->GetLocalX();
			yCoordinates = car->GetLocalY() - checkpointArr[i]->GetLocalY();
			zCoordinates = car->GetLocalZ() - checkpointArr[i]->GetLocalZ();
			/*calculate distance*/
			distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			/*collision occurred*/
			if (distance < CAR_RADIUS + cp_radius) {
				if (check_skipped_cp[i-1] == 1) { //and if checkpoint 2 was completed then change the game state
					if (currentLap == LAP_1) {
						current_game_state_int = THIRD_CHECKPOINT_LAP2;
					}
					else {
						current_game_state_int = THIRD_CHECKPOINT;
					}
					current_game_state = STAGE_3_COMPLETE_STATE;
					check_skipped_cp[i] = 1;
					createCrossX = checkpointArr[i]->GetLocalX();
					createCrossY = checkpointArr[i]->GetLocalY();
					createCrossZ = checkpointArr[i]->GetLocalZ();
					crossYRotate = 90.0f;
					if (cross_state == NO_CROSS) {//Create the cross model 
						cross_state = CREATE_CROSS;
					}
				}
				else {
					outText << "Checkpoint "<<i<<" Missed!" << endl;
					myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
					outText.str(""); // Clear myStream
				}
			}
			break;
		case FOURTH_CHECKPOINT:

			xCoordinates = car->GetLocalX() - checkpointArr[i]->GetLocalX();
			yCoordinates = car->GetLocalY() - checkpointArr[i]->GetLocalY();
			zCoordinates = car->GetLocalZ() - checkpointArr[i]->GetLocalZ();
			/*calculate distance*/
			distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			/*collision occurred*/
			if (distance < CAR_RADIUS + cp_radius) {
				if (check_skipped_cp[i - 1] == 1) { //and if checkpoint 3 was completed then change the game state
					if (currentLap == LAP_1) {
						current_game_state_int = FOURTH_CHECKPOINT_LAP2;
					}
					else {
						current_game_state_int = FOURTH_CHECKPOINT;
					}
					current_game_state = STAGE_4_COMPLETE_STATE;
					check_skipped_cp[i] = 1;
					createCrossX = checkpointArr[i]->GetLocalX();
					createCrossY = checkpointArr[i]->GetLocalY();
					createCrossZ = checkpointArr[i]->GetLocalZ();
					crossYRotate = 30.0f;
					if (cross_state == NO_CROSS) {//Create the cross model 
						cross_state = CREATE_CROSS;
					}
				}
				else {
					outText << "Checkpoint " << i << " Missed!" << endl;
					myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
					outText.str(""); // Clear myStream
				}
			}
			break;
		case FIFTH_CHECKPOINT:

			xCoordinates = car->GetLocalX() - checkpointArr[i]->GetLocalX();
			yCoordinates = car->GetLocalY() - checkpointArr[i]->GetLocalY();
			zCoordinates = car->GetLocalZ() - checkpointArr[i]->GetLocalZ();
			/*calculate distance*/
			distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			/*collision occurred*/
			if (distance < CAR_RADIUS + cp_radius) {
				if (check_skipped_cp[i - 1] == 1) { //and if checkpoint 4 was completed then change the game state
					if (currentLap == LAP_1) {
						current_game_state_int = FIFTH_CHECKPOINT_LAP2;
					}
					else {
						current_game_state_int = FIFTH_CHECKPOINT;
					}
					current_game_state = STAGE_5_COMPLETE_STATE;
					check_skipped_cp[i] = 1;
					createCrossX = checkpointArr[i]->GetLocalX();
					createCrossY = checkpointArr[i]->GetLocalY();
					createCrossZ = checkpointArr[i]->GetLocalZ();
					crossYRotate = 0.0f;
					if (cross_state == NO_CROSS) {//Create the cross model 
						cross_state = CREATE_CROSS;
					}
				}
				else {
					outText << "Checkpoint " << i << " Missed!" << endl;
					myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
					outText.str(""); // Clear myStream
				}
			}
			break;
		case LAST_CHECKPOINT:
			xCoordinates = car->GetLocalX() - checkpointArr[i]->GetLocalX();
			yCoordinates = car->GetLocalY() - checkpointArr[i]->GetLocalY();
			zCoordinates = car->GetLocalZ() - checkpointArr[i]->GetLocalZ();
			/*calculate distance*/
			distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			/*collision occurred*/
			if (distance < CAR_RADIUS + cp_radius) {
				if (check_skipped_cp[i - 1] == 1) { //and if checkpoint 5 was completed then change the game state
					if (currentLap == LAP_1) {
						current_game_state_int = LAST_CHECKPOINT_LAP2;
					}
					else {
						current_game_state_int = LAST_CHECKPOINT;
					}
					current_game_state = STAGE_0_COMPLETE_STATE;
					check_skipped_cp[i] = 1;
					hasCollidedOnce = false;//reset the hasCollidedOnce to false again
					createCrossX = checkpointArr[i]->GetLocalX();
					createCrossY = checkpointArr[i]->GetLocalY();
					createCrossZ = checkpointArr[i]->GetLocalZ();
					crossYRotate = 90.0f;
					if (cross_state == NO_CROSS) {//Create the cross model 
						cross_state = CREATE_CROSS;
					}
				}
				else {
					outText << "Checkpoint " << i << " Missed!" << endl;
					myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
					outText.str(""); // Clear myStream
				}
			}
			break;
		}
	}
}
		
/*sphere to sphere collision (car collision with stationary objects)*/
bool sphere_to_sphere_general(IModel* object, IModel* objectArr[], int object_size, float object_radius) {
	for (int i = 0; i < object_size; i++) {
		/*Front wing*/
		double xCoordinates = object->GetX() - objectArr[i]->GetLocalX();
		double yCoordinates = object->GetY() - objectArr[i]->GetLocalY();
		double zCoordinates = object->GetZ() - objectArr[i]->GetLocalZ();

		/*Calculate the distance from car to other object*/
		double distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
		/*Collision occurred*/
		/*front wing*/
		if (distance < CAR_RADIUS + object_radius) {
			return true;
		}
	}
	return false;
}

/*sphere to sphere collision (car collision with speed packages, upon collision destroy the speed package)*/
bool sphere_to_sphere_speedPack(IModel* car, IModel* speedBoost[], IMesh* speedBoostMesh) {
	for (int i = 0; i < SPEEDBOOST_SIZE; i++) {
		if (speedBoost[i] != 0) {//check for collision if speedboost exists
			double xCoordinates = car->GetX() - speedBoost[i]->GetLocalX();
			double yCoordinates = car->GetY() - speedBoost[i]->GetLocalY();
			double zCoordinates = car->GetZ() - speedBoost[i]->GetLocalZ();
			/*Calculate the distance from car to other object*/
			double distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
			/*Collision occurred*/
			/*front wing*/
			if (distance < CAR_RADIUS + SPEED_BOOST_RADIUS) {
				speedBoostMesh->RemoveModel(speedBoost[i]);//delete speedboost uppon collision
				speedBoost[i] = 0;//speedboost doesnt exists thus dont skip for collision
				return true;
			}
		}
	}
	return false;
}

bool sphere_to_sphere_npc(IModel* car, CPlayer npc) {
	/*Get the coordinates*/
	double xCoordinates = car->GetX() - npc.GetModel()->GetLocalX();
	double yCoordinates = car->GetY() - npc.GetModel()->GetLocalY();
	double zCoordinates = car->GetZ() - npc.GetModel()->GetLocalZ();

	double distance = sqrt(pow(xCoordinates, 2.0) + pow(yCoordinates, 2.0) + pow(zCoordinates, 2.0));
	/*Collision occurred*/
	if (distance < CAR_RADIUS + npc.GetNpcRadius()) {
		return true;
	}
	else {
		return false;
	}
}

/*******************************************COLLISION FUNCTIONS ENDS*******************************************/

/*******************************************EXTRA FUNCTIONS USED START*******************************************/
/*Change camera mode function*/
void change_camera(ICamera* myCamera, IModel* car, int mCameraState) {
	float cameraXcoord = 0.0f, cameraYcoord = 0.0f, cameraZcoord = 0.0f, cameraRotX = 0.0f, cameraRotY = 0.0f, cameraRotZ = 0.0f;

	/*Reset camera orientation and position*/
	myCamera->SetLocalPosition(cameraXcoord, cameraYcoord, cameraZcoord);
	myCamera->ResetOrientation();
	myCamera->DetachFromParent();

	/*Change the camera state*/
	switch (mCameraState) {
		case CAMERA_STATE_THIRD: {
			cameraXcoord = 0.0f;
			cameraYcoord = 20.0f;
			cameraZcoord = -25.0f;
			cameraRotX = 26.0f;
			myCamera->RotateLocalX(cameraRotX);
			myCamera->SetLocalPosition(cameraXcoord, cameraYcoord, cameraZcoord);
			myCamera->AttachToParent(car);
			break;
		}
		case CAMERA_STATE_FIRST: {
			cameraXcoord = 0.0f;
			cameraYcoord = 10.0f;
			cameraZcoord = 0.0f;
			cameraRotX = 26.0f;
			myCamera->SetLocalPosition(cameraXcoord, cameraYcoord, cameraZcoord);
			myCamera->RotateLocalX(cameraRotX);
			myCamera->AttachToParent(car);
			break;
		}
		case CAMERA_STATE_SURVEILLANCE: {
			cameraXcoord = 68.0f;
			cameraYcoord = 195.0f;
			cameraZcoord = 388.0f;
			cameraRotX = 15.0f;
			cameraRotY = 35.0f;
			cameraRotZ = -20.0f;
			myCamera->SetLocalPosition(cameraXcoord, cameraYcoord, cameraZcoord);
			myCamera->AttachToParent(car);
			myCamera->LookAt(car);
			myCamera->RotateLocalY(cameraRotY);
			myCamera->RotateLocalX(cameraRotX);
			myCamera->RotateLocalZ(cameraRotZ);
			break;
		}
		case CAMERA_STATE_FREE: {
			cameraXcoord = 196.0f;
			cameraYcoord = 117.0f;
			cameraZcoord = -133.0f;
			cameraRotX = 15.0f;
			cameraRotY = -60.0f;
			myCamera->SetLocalPosition(cameraXcoord, cameraYcoord, cameraZcoord);
			myCamera->RotateLocalY(cameraRotY);
			myCamera->RotateLocalX(cameraRotX);
			break;
		}
	}
}

/*Function that moves the hover*/
void moveHover(I3DEngine* myEngine, IModel* car, ICamera* myCamera, float &dt, float &acceleration){
	float limitSpeed = 0.0f;
	int roundSpeed = 1000;
	float fastSpeed = 150.0f, mediumSpeed = 100.0f;

	/*Reverse speed on collision to give that bounce effect*/
	if (front_side_hit) {
		/*Reverse speed only when the hover has a positive velocity(it has clipping in the wall before i added that)*/
		if (!hasCollided) {
			/*Reduce speed uppon collision and HP*/
			if (roundf(velocity * roundSpeed) >= fastSpeed) { /*If the car is going above 75% of its speed uppon collision reduce speed by 75% */
				carHP -= 15;
				reduceVelocityBy = BIG_IMPACT;//0.25f;
			}
			else if (roundf(velocity * roundSpeed) < fastSpeed && roundf(velocity * roundSpeed) >= mediumSpeed) {/*If the car is going above 50% of its speed uppon collision reduce speed by 50% */
				carHP -= 10;
				reduceVelocityBy = MEDIUM_IMPACT;//0.50f;
			}
			else {/*car is going below 50% of its speed so reduce speed by 25%*/
				carHP -= 5;
				reduceVelocityBy = SMALL_IMPACT;//0.75f;
			}
			/*Update the new velocity after collision*/
			velocity *= -reduceVelocityBy;
			hasCollided = true;
		}
		if (velocity >= limitSpeed) { //velocity >= 0
			hasCollided = false;
		}
	}

	/*If back side hit just reverse the velocity to bounce back*/
	else if (back_side_hit) {
		velocity = -velocity;
	}

	if (overheat) {//if the hover overheated change its top speeds
		top_speed = 70.0f;
		top_speed_bw = -25.0f;
	}
	else {
		top_speed = 200.0f;
		top_speed_bw = -75.0f;
	}

	/*When W key is held accelerate the hover*/
	if (myEngine->KeyHeld(Key_W)) {
		if (roundf(velocity * roundSpeed) <= top_speed) {
			velocity += acceleration*dt;
		}
	}
	/*When W key is not held deccelerate due to friction*/
	else if (velocity != limitSpeed && velocity > limitSpeed) {
		velocity -= friction*dt;
	}

	/*When S key is held deccelerate the hover*/
	if (myEngine->KeyHeld(Key_S)) {
		if (roundf(velocity * roundSpeed) > top_speed_bw) {
			velocity -= ACCEL_BW*dt;
		}
	}
	/*When in reverse but S keyis not held accelerate due to friction*/
	else if (velocity != limitSpeed && velocity < limitSpeed) {
		velocity += friction*dt;
	}


	/*Steers the car clockwise*/
	if (myEngine->KeyHeld(Key_D)) {
		car->RotateY(kSteerSpeed*dt);
	}
	
	
	/*Steers the car anti-clockwise*/
	if (myEngine->KeyHeld(Key_A)) {
		car->RotateY(-kSteerSpeed*dt);
	}


	/*Make the hover float up and down*/
	float pos = car->GetLocalY();

	if (pos < LIMIT_FLOAT_TOP) {
		velocityY += GRAVITY*dt;
	}
	else if (pos > LIMIT_FLOAT_BOTTOM) {
		velocityY += -GRAVITY*dt;
	}

	car->MoveLocal(0, velocityY, velocity);


}/*Function for the boost facility*/

void boostFacility(I3DEngine* myEngine, IFont* myFont2, int &boost, float &acceleration) {

	float boostedAcceleration = 0.075f; //accel on boost
	float previousAcceleration = 0.050f; //accel off boost
	float velocityOnOverheat = velocity / 3.0f; //overheated state speed

	switch (boost) {
	case BOOST_OFF://default state of the boost
		overheat = false;
		if (myEngine->KeyHit(Key_Space)) {
			boost = BOOST_ON;//if space was hit transition to boost on state
			time(&startBoost);
			time(&endBoost);
			acceleration = boostedAcceleration;//change acceleration to on boost acceleration
		}
		boost_text << "Boost State: Available" << endl;
		myFont2->Draw(boost_text.str(), FONT_X_BOOST_STATE, FONT_Y_BOOST_STATE, kWhite);
		boost_text.str(""); // Clear myStream
		break;
	case BOOST_ON:
		timeDiffBoost = difftime(endBoost, startBoost);
		if (myEngine->KeyHeld(Key_Space)) {
			time(&endBoost);
			if (timeDiffBoost < 2) {//if space was held for less than 2 seconds e.g on boost state for less than 2 seconds d
				boost_text << "Boost State: Active " << endl;
				myFont2->Draw(boost_text.str(), FONT_X_BOOST_STATE, FONT_Y_BOOST_STATE, kWhite);
				boost_text.str("");
			}
			else if (timeDiffBoost < 4) {//if space was held for more than 2 seconds e.g on boost state for more than 2 seconds d
				boost_text << "Boost State: Active " << endl;
				boost_text << "WARNING: " << 4 - timeDiffBoost << " SECONDS BEFORE BOOST OVERHEATS" << endl;
				myFont2->Draw(boost_text.str(), FONT_X_BOOST_STATE, FONT_Y_BOOST_STATE, kWhite);
				boost_text.str("");
			}
			else {//transition to overheat state 
				overheat = true;
				boost_text << "Boost State: OVERHEATED " << endl;
				myFont2->Draw(boost_text.str(), FONT_X_BOOST_STATE, FONT_Y_BOOST_STATE, kWhite);
				boost_text.str("");
				boost = BOOST_OVERHEAT;
				time(&startOverheat);
				velocity = velocityOnOverheat;
			}
		}
		else {
			//When space was released
			//change state back to boost off and change the acceleration back to the 'original'
			boost = BOOST_OFF;
			acceleration = previousAcceleration;
		}
		break;
	case BOOST_OVERHEAT://overheat state
		time(&endOverheat);
		timeDiffOverheat = difftime(endOverheat, startOverheat);
		boost_text << "Boost State: OVERHEATED " << endl;
		boost_text << 6 - timeDiffOverheat << " seconds before boost available" << endl;
		myFont2->Draw(boost_text.str(), FONT_X_BOOST_STATE, FONT_Y_BOOST_STATE, kWhite);
		boost_text.str(""); // Clear myStream
		if (timeDiffOverheat > 6) {
			boost = BOOST_OFF;
			acceleration = previousAcceleration;
			overheat = false;
		}

	}
}

/*Function for doubling velocity upon collision with a speed pack*/
void speedPackage(IModel* car, IModel* speedBoost[], IMesh* speedBoostMesh) {
	float previousFriction = 0.025f; //normal friction OR friction before power boost
	switch (power_state) {
	case OFF_POWER_BOOST:
		if (sphere_to_sphere_speedPack(car, speedBoost, speedBoostMesh)) {
			velocity *= 2.0f;//double the velocity
			time(&startPowerBoost);
			time(&endPowerBoost);
			friction = 0;
			power_state = ON_POWER_BOOST;
		}
		break;
	case ON_POWER_BOOST:
		time(&endPowerBoost);
		powerBoostTimeDiff = difftime(endPowerBoost, startPowerBoost);
		if (powerBoostTimeDiff >= 2) {
			velocity /= 2.0f; //when 2 seconds pass revert the speed back to the previous one
			friction = previousFriction;
			power_state = OFF_POWER_BOOST;
		}
		break;
	}
}

/*Function that moves the camera within its limits according to its state*/
void moveCamera(I3DEngine* myEngine, ICamera* myCamera, int mCameraState, int cameraMovement, float &dt) {
	dt = myEngine->Timer();

	float cameraXCoordinate = myCamera->GetLocalX();
	float cameraYCoordinate = myCamera->GetLocalY();
	float cameraZCoordinate = myCamera->GetLocalZ();

	/*Limits for the cameras' movement*/
	float limitForward = 0.0f, limitBackwards = 0.0f, limitLeft = 0.0f, limitRight = 0.0f;
	switch (mCameraState) {
		/*Camera controlls for free state camera*/
	case CAMERA_STATE_FREE:
		switch (cameraMovement) {
		case MOVE_CAMERA_FORWARD:
			limitForward = 20.0f;
			if (cameraZCoordinate < limitForward) {
				myCamera->MoveLocalZ(CAMERA_VELOCITY * dt);
			}
			break;
		case MOVE_CAMERA_BACKWARDS:
			limitBackwards = -200.0f;
			if (cameraZCoordinate > limitBackwards) {
				myCamera->MoveLocalZ(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_LEFT:
			limitLeft = 50.0f;
			if (cameraXCoordinate > limitLeft) {
				myCamera->MoveLocalX(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_RIGHT:
			limitRight = 300.0f;
			if (cameraXCoordinate < limitRight) {
				myCamera->MoveLocalX((CAMERA_VELOCITY * dt));
			}
			break;
		}
		break;//end of free state case

			  /*Camera controlls for first person state camera*/
	case CAMERA_STATE_FIRST:
		switch (cameraMovement) {
		case MOVE_CAMERA_FORWARD:
			limitForward = 5.0f;
			if (cameraZCoordinate < limitForward) {
				myCamera->MoveLocalZ(CAMERA_VELOCITY * dt);
			}
			break;
		case MOVE_CAMERA_BACKWARDS:
			limitBackwards = -10.0f;
			if (cameraZCoordinate > limitBackwards) {
				myCamera->MoveLocalZ(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_LEFT:
			limitLeft = -5.0f;
			if (cameraXCoordinate > limitLeft) {
				myCamera->MoveLocalX(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_RIGHT:
			limitRight = 5.0f;
			if (cameraXCoordinate < limitRight) {
				myCamera->MoveLocalX((CAMERA_VELOCITY * dt));
			}
			break;
		}
		break;//end of first person state case

			  /*Camera controlls for third person state camera*/
	case CAMERA_STATE_THIRD:
		switch (cameraMovement) {
		case MOVE_CAMERA_FORWARD:
			limitForward = -18.0f;
			if (cameraZCoordinate < limitForward) {
				myCamera->MoveLocalZ(CAMERA_VELOCITY * dt);
			}
			break;
		case MOVE_CAMERA_BACKWARDS:
			limitBackwards = -40.0f;
			if (cameraZCoordinate > limitBackwards) {
				myCamera->MoveLocalZ(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_LEFT:
			limitLeft = -15.0f;
			if (cameraXCoordinate > limitLeft) {
				myCamera->MoveLocalX(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_RIGHT:
			limitRight = 15.0f;
			if (cameraXCoordinate < limitRight) {
				myCamera->MoveLocalX((CAMERA_VELOCITY * dt));
			}
			break;
		}
		break;//end of third state case

			  /*Camera controlls for third person state camera*/
	case CAMERA_STATE_SURVEILLANCE:
		switch (cameraMovement) {
		case MOVE_CAMERA_FORWARD:
			limitForward = 300.0f;
			if (cameraZCoordinate > limitForward) {
				myCamera->MoveLocalZ(CAMERA_VELOCITY * dt);
			}
			break;
		case MOVE_CAMERA_BACKWARDS:
			limitBackwards = 450.0f;
			if (cameraZCoordinate < limitBackwards) {
				myCamera->MoveLocalZ(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_LEFT:
			limitLeft = 240.0f;
			if (cameraXCoordinate < limitLeft) {
				myCamera->MoveLocalX(-(CAMERA_VELOCITY * dt));
			}
			break;
		case MOVE_CAMERA_RIGHT:
			limitRight = 0.0f;
			if (cameraXCoordinate > limitRight) {
				myCamera->MoveLocalX((CAMERA_VELOCITY * dt));
			}
			break;
		}
		break;//end of surveillance state case
	}
}

/*Function that handles the count-down functionality*/
void countDown(IFont* myFont, string &current_game_state, time_t start) {
	int timeLimit = 0, secToStart = 3;
	time_t timeDiff, end;

	time(&end);
	/*get how many secs have passed since the space was pressed (transition from demo -> countdown)*/
	timeDiff = secToStart - difftime(end, start);

	/*3 - 2 - 1 message*/
	if (timeDiff>timeLimit) {
		outText << timeDiff << endl;
		myFont->Draw(outText.str(), font_x_cnt_down, font_y_cnt_down, kRed);
		outText.str(""); // Clear myStream
	}
	else if (timeDiff == timeLimit) {
		outText << "Go!" << endl;
		myFont->Draw(outText.str(), font_x_cnt_down, font_y_cnt_down, kRed);
		outText.str(""); // Clear myStream
	}
	/*Transition to STAGE_0_COMPLETE*/
	else {
		current_game_state = STAGE_0_COMPLETE_STATE;
		time(&startRace);//Take the time when the race started
	}
}

/*Function that creates the checkpoint cross and deletes it after a certain time*/
void createCross(IMesh* crossMesh, IModel* cross[]) {
	float addHeight = 10.0f, scaleCrossDownBy = 0.50f;
	int secsToDelete = 1;
	switch (cross_state) {
		case NO_CROSS:
			time(&startCross);
			time(&endCross);
			break;
		case CREATE_CROSS:
			time(&startCross);
			time(&endCross);
			cross[0] = crossMesh->CreateModel(createCrossX, createCrossY + addHeight, createCrossZ);
			cross[0]->Scale(scaleCrossDownBy);
			cross[0]->RotateLocalY(crossYRotate);
			cross_state = DELETE_CROSS;
			break;
		case DELETE_CROSS:
			time(&endCross);
			if (difftime(endCross, startCross) > secsToDelete) {
				crossMesh->RemoveModel(cross[0]);
				createCrossX = 0.0f;
				createCrossY = 0.0f;
				createCrossZ = 0.0f;
				crossYRotate = 0.0f;
				cross_state = NO_CROSS;
			}
	}
}

void showPos(CPlayer npc, IModel* car, IFont* myFont) {
	float height = 50.0f;
	/*If npcs state changed first that means its it passed the checkpoint first thus being first*/
	if (npc.GetGameState() > current_game_state_int) {
		showRankingText = NPC_IS_FIRST;
	}
	else if (npc.GetGameState() < current_game_state_int) {
		showRankingText = PLAYER_IS_FIRST;
	}
	

	switch (showRankingText) {
		case NPC_IS_FIRST:
			show_position_text << "Pos 2 / 2" << endl;
			myFont->Draw(show_position_text.str(), LAP_X, LAP_X + height, kWhite);
			show_position_text.str(""); // Clear myStream
			break;
		case PLAYER_IS_FIRST:
			show_position_text << "Pos 1 / 2" << endl;
			myFont->Draw(show_position_text.str(), LAP_X, LAP_X + height, kBlack);
			show_position_text.str(""); // Clear myStream
			break;

	}
}


/*******************************************EXTRA FUNCTIONS USED ENDS*******************************************/

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	/*******************************************VARIABLES USED STARTS*******************************************/

	int current_camera = CAMERA_STATE_FREE, mouseMoveX, mouseMoveY, cam_steering = 0, boost = BOOST_OFF;
	/**Array for holding the coordinates of all the objects in the game**/
	double wall_z_min[WALL_SIZE], wall_z_max[WALL_SIZE], wall_y_min[WALL_SIZE], wall_y_max[WALL_SIZE], wall_x_min[WALL_SIZE], wall_x_max[WALL_SIZE];
	double  tank_z_min[TANK_SIZE], tank_z_max[TANK_SIZE], tank_x_min[TANK_SIZE], tank_x_max[TANK_SIZE], tank_y_min[TANK_SIZE], tank_y_max[TANK_SIZE];
	/**Array for holding the coordinates of all the objects in the game ENDS**/
	bool collision = false, checkpoint_collision = false, pause = false, default_camera_mode = true, reset_camera = false, getTimeDiffOnce = false;
	/*Game state variables*/
	bool check_skipped_cp[CHECKPOINT_SIZE] = { 0 };// initialize tha array with false
	string current_game_state = DEMO_STATE; //set the first state to be the Demo State
	string winner_hover;
	time_t start;
	float acceleration = 0.050f;
	
   /*******************************************VARIABLES USED ENDS*******************************************/

	// Add custom  folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Assignment3");

	/*Camera Set Up*/
	ICamera* myCamera = myEngine->CreateCamera(kManual); //submitted by accident kFPS instead of kManual
	myCamera->SetLocalPosition(196, 117, -133);
	myCamera->RotateLocalY(-60);
	myCamera->RotateLocalX(15);

	/*******************************************LOAD MODELS AND MESHES STARTS*******************************************/
	/*Load Skybox*/
	IMesh* skyboxMesh = myEngine->LoadMesh("Skybox 07.x");
	IModel* skybox = skyboxMesh->CreateModel(0, -960, 0);

	/*Load ground*/
	IMesh* groundMesh = myEngine->LoadMesh("ground.x");
	IModel* ground = groundMesh->CreateModel(0, 0, 0);

	/*Load Checkoints*/
	IMesh* checkpointMesh = myEngine->LoadMesh("Checkpoint.x");
	IModel* checkpointArr[CHECKPOINT_SIZE];
	/*Load crosses*/
	IMesh* crossMesh = myEngine->LoadMesh("Cross.x");
	IModel* cross[1];

	/*Load Isles*/
	IMesh* isle_straight_Mesh = myEngine->LoadMesh("IsleStraight.x");
	IMesh* isle_cross_Mesh = myEngine->LoadMesh("IsleCorner.x");
	IMesh* isle_corner_Mesh = myEngine->LoadMesh("IsleCross.x");
	IModel* isleStraightArr[ISLE_SIZE];
	IModel* isleCornerArr[ISLE_CORNER_SIZE];
	IModel* isleCrossArr[ISLE_SIZE2];


	/*Load race car*/
	IMesh* carMesh = myEngine->LoadMesh("race2.x");
	IModel* car = carMesh->CreateModel(0, 0, -40);
	car->SetSkin("glass_red.jpg");
	CPlayer npc = CPlayer( carMesh, 0.0f, 0.0f, -20.0f);//npc

	/*Load walls*/
	IMesh* wallMesh = myEngine->LoadMesh("Wall.x");
	IModel* wallArr[WALL_SIZE];

	/*Load water tanks*/
	IMesh* tankMesh = myEngine->LoadMesh("TankLarge2.x");
	IModel* tankArr[TANK_SIZE];

	/*Load tribune*/
	IMesh* tribuneMesh = myEngine->LoadMesh("Tribune1.x");
	IModel* tribuneArr[TRIBUNE_SIZE];


	/*Load front car dummy and back car dummy*/
	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x"); /*TODO DELETE LATER*/
	/*An array that will store dummy
	models that will be used to detect
	collision between the checkpoint sides*/
	IModel* cp_dummyArr[CHECKPOINT_LEGS_SIZE];
	IModel* wayPointsArr[WAY_POINTS_SIZE];

	IModel* dummyFront = dummyMesh->CreateModel(0, 0, 2.5); /*dummyFront will act as the front wing of our car to detect collisions in front*/
	IModel* dummyBack = dummyMesh->CreateModel(0, 0, -2.5); /*dummyBack will act as the back area of our car to detect any collision in the back*/
	dummyFront->AttachToParent(car); /*attack them to the car */
	dummyBack->AttachToParent(car);

	/*Load speed boosts*/
	IMesh* speedBoostMesh = myEngine->LoadMesh("Flare.x");
	IModel* speedBoost[SPEEDBOOST_SIZE];
	speedBoost[0] = speedBoostMesh->CreateModel(-62, 2, 278);
	speedBoost[1] = speedBoostMesh->CreateModel(-312, 2, -46);
	speedBoost[2] = speedBoostMesh->CreateModel(-54, 2, -83);

	// mouse capture
	myEngine->StartMouseCapture();
	bool mouseCaptureActive = false; // state of mouse capture


	/*******************************************LOAD MODELS AND MESHES ENDS*******************************************/

	
	/*Call load game scene object functions*/
	load_checkpoint(checkpointMesh, checkpointArr);
	load_walls_left (wallMesh, wallArr);
	load_walls_right(wallMesh, wallArr);
	load_isles(isle_straight_Mesh, isleStraightArr, isle_cross_Mesh,isleCrossArr);
	load_isles_corner(isle_corner_Mesh, isleCornerArr);
	load_tribune(tribuneMesh, tribuneArr);
	load_water_tanks(tankMesh, tankArr, tank_z_min, tank_z_max, tank_y_min,tank_y_max,tank_x_min,tank_x_max);
	load_cpoints_dummies(dummyMesh, cp_dummyArr);
	get_coord_walls(wallMesh, wallArr, wall_z_min, wall_z_max, wall_y_min, wall_y_max, wall_x_min, wall_x_max);
	load_waypoints(dummyMesh, wayPointsArr);

	/*Load font*/
	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 40);
	IFont* myFont2 = myEngine->LoadFont("Comic Sans MS", 17);
	ISprite* backdrop = myEngine->CreateSprite("custom_backdrop.png", sprite_x, sprite_y);
	
	float dt=myEngine->Timer();

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		
		myEngine->DrawScene();

		npc.SetVelocity(NPC_VELOCITY, dt);
		npc.SetRadius(NPC_RADIUS);

		dt = myEngine->Timer();


		/*Display in the backdrop*/
		current_game_state_text <<"Current State: "<< current_game_state << endl;
		current_velocity << "KM/H: " <<roundf(velocity*1000);
		hover_hp << "HP: " << carHP;
		lap_text << "Lap  " << currentLap+1 << " / " << LAP_SIZE << endl;//current lap starts at 0 sto add + 1

		myFont2->Draw(current_game_state_text.str(), FONT_X_CURRENT_GAME_STATE, FONT_Y_CURRENT_GAME_STATE, kWhite);
		myFont2->Draw(current_velocity.str(), FONT_X_CURRENT_VELOCITY, FONT_Y_CURRENT_VELOCITY, kWhite);
		myFont2->Draw(hover_hp.str(), FONT_X_CURRENT_VELOCITY+70.0f, FONT_Y_CURRENT_VELOCITY, kWhite);
		myFont->Draw(lap_text.str(), LAP_X, LAP_Y, kBlack);


		hover_hp.str("");
		current_game_state_text.str("");
		current_velocity.str("");
		lap_text.str("");


		/*Pause game with key P only when count down is completed*/
		if (myEngine->KeyHit(Key_P)) {
			if (current_game_state!=DEMO_STATE && current_game_state!=COUNTDOWN_STATE) {
				pause = !pause;
			}
		}
		else if(pause) {
			/*Display the pause state message*/
			outText << "Press 'P' to Unpause" << endl;
			myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
			outText.str(""); // Clear myStream
		}

		/*Terminate game once escape key pressed*/
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}

		/*If in demoState user should not be able to press anything*/
		
		if (!pause) {	
			/**Constantly check for any collision happening**/
			if (sphere_to_box(dummyFront,tank_z_min,tank_z_max,tank_y_min,tank_y_max,tank_x_min,tank_x_max) ||
				sphere_to_sphere_general(dummyFront, cp_dummyArr, CHECKPOINT_LEGS_SIZE, cp_dummy_radius) ||
				sphere_to_sphere_general(dummyFront, isleStraightArr, ISLE_SIZE, isleRadius) ||
				sphere_to_sphere_general(dummyFront, isleCrossArr, ISLE_SIZE2, ISLE_CROSS_RADIUS) ||
				sphere_to_box(dummyFront, wall_z_min, wall_z_max, wall_y_min,wall_y_max, wall_x_min, wall_x_max)||
				sphere_to_sphere_general(dummyFront, isleCornerArr, ISLE_CORNER_SIZE, ISLE_CORNER_RADIUS)||
				sphere_to_sphere_npc(dummyFront, npc)) {
				front_side_hit = true;
			}
			else {
				front_side_hit = false;
			}
			/*Check for any collision between the back of the car*/
			if (sphere_to_sphere_general(dummyBack, cp_dummyArr, CHECKPOINT_LEGS_SIZE, cp_dummy_radius) ||
				sphere_to_box(dummyBack, tank_z_min, tank_z_max, tank_y_min, tank_y_max, tank_x_min, tank_x_max) ||
				sphere_to_sphere_general(dummyBack, isleStraightArr, ISLE_SIZE, isleRadius) ||
				sphere_to_sphere_general(dummyBack, isleCrossArr, ISLE_SIZE2, ISLE_CROSS_RADIUS) ||
				sphere_to_box(dummyBack, wall_z_min, wall_z_max, wall_y_min, wall_y_max, wall_x_min, wall_x_max)||
				sphere_to_sphere_general(dummyBack, isleCornerArr, ISLE_CORNER_SIZE, ISLE_CORNER_RADIUS)||
				sphere_to_sphere_npc(dummyBack, npc)) {
				back_side_hit = true;
			}
			else {
				back_side_hit = false;
			}

			/*Check if player reached the checkpoints*/
			sphere_to_sphere_cp(car, checkpointArr,current_game_state,myFont,check_skipped_cp,winner_hover);

		}
		/*Demo state*/
		if (current_game_state==DEMO_STATE) {
			/*Display the demo state message*/
			outText << "Press Space to Start" << endl;
			myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
			outText.str(""); // Clear myStream
			
			/*Transition from Demo State -> Countdown State*/
			if (myEngine->KeyHit(Key_Space)) {
				current_game_state = COUNTDOWN_STATE;
				time(&start);//get the time when the transition to count-down state occurred
			}
		}
		/*Count Down state*/
		if (current_game_state==COUNTDOWN_STATE) {
			countDown(myFont, current_game_state, start);
		}

		/*Function that moves the hover*/
		if ((current_game_state != DEMO_STATE && current_game_state != COUNTDOWN_STATE && current_game_state != OVER_STATE && !pause)) {
			if (carHP > 1) {
				moveHover(myEngine, car, myCamera, dt, acceleration);
				boostFacility(myEngine, myFont2, boost, acceleration);
				speedPackage(dummyFront, speedBoost, speedBoostMesh);
				npc.UpdateHover(wayPointsArr, current_game_state,winner_hover);
				createCross(crossMesh, cross);
				showPos(npc, car, myFont);
			}
			else {
				current_game_state = DEAD_STATE;
			}
		}

		/*The car is broken display a message to the player*/
		if (current_game_state == DEAD_STATE) {
			/*Display the demo state message*/
			outText << "You Lost. Your hover is broken" << endl;
			outText << "Press 'Esc' and play again!" << endl;
			myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
			outText.str(""); // Clear myStream

		}

		/*Over state - Display who won and their time*/
		if (current_game_state == OVER_STATE) {
			/*Get their difference only once*/
			if (!getTimeDiffOnce) {
				time(&endRace);
				timeDiffRace = difftime(endRace,startRace);
				getTimeDiffOnce = true;
			}
			outText << winner_hover<<" WON!";
			outText << "Time "<<timeDiffRace<<" Seconds";
			myFont->Draw(outText.str(), FONT_X, FONT_Y, kBlack);
			outText.str(""); // Clear myStream

		}


		/***CAMERAS SECTION***/
		if (!pause) {

			if (!mouseCaptureActive || mouseCaptureActive){
				int mouseMoveX = myEngine->GetMouseMovementX();
				myCamera->RotateY(mouseMoveX * MouseRotation * dt); // the MouseRotation reduces the rotation speed

				int mouseMoveY = myEngine->GetMouseMovementY();
				myCamera->RotateLocalX(mouseMoveY * MouseRotation * dt); // the MouseRotation reduces the rotation speed

				float mouseMoveWheel = myEngine->GetMouseWheelMovement();
				myCamera->MoveLocalZ(mouseMoveWheel * WheelMove * dt); // the MouseRotation reduces the rotation speed
			}

			/*toggle mouse capture*/
			if (myEngine->KeyHit(Key_Tab)){
				if (mouseCaptureActive){
					myEngine->StopMouseCapture();
					mouseCaptureActive = false;
				}
				else{
					myEngine->StartMouseCapture();
					mouseCaptureActive = true;
				}
			}

			/**CAMERA MOVEMENT CONTROLLS STARTS**/

			/*Move Camera FORWARDS according to its limits and camera state*/
			if (myEngine->KeyHeld(Key_Up)) {
				moveCamera(myEngine,myCamera, current_camera, MOVE_CAMERA_FORWARD,dt);
			}

			/*Move BACKWARDS according to its limits and camera state*/
			if (myEngine->KeyHeld(Key_Down)) {
				moveCamera(myEngine, myCamera, current_camera, MOVE_CAMERA_BACKWARDS, dt);
			}

			/*Move LEFT according to its limits and camera state*/
			if (myEngine->KeyHeld(Key_Left)) {
				moveCamera(myEngine, myCamera, current_camera, MOVE_CAMERA_LEFT, dt);
			}
			/*Move Right according to its limits and camera state*/
			if (myEngine->KeyHeld(Key_Right)) {
				moveCamera(myEngine, myCamera, current_camera, MOVE_CAMERA_RIGHT, dt);
			}

			/**CAMERA MOVEMENT CONTROLLS ENDS**/

			/**SWITCH THE CAMERA STATE CONTROLLS STARTS**/

			/*First Person Camera*/
			if (myEngine->KeyHit(Key_1)) {
				change_camera(myCamera, car, CAMERA_STATE_FIRST);
				current_camera = CAMERA_STATE_FIRST;
			}

			/*Free Moving Camera*/
			if (myEngine->KeyHit(Key_2)) {
				change_camera(myCamera, car, CAMERA_STATE_FREE);
				current_camera = CAMERA_STATE_FREE;
			}

			/*Chase Camera*/
			if (myEngine->KeyHit(Key_3)) {
				change_camera(myCamera, car, CAMERA_STATE_THIRD);
				current_camera = CAMERA_STATE_THIRD;
			}
	
			/*Surveillance Camera*/
			if (myEngine->KeyHit(Key_4)) {
				change_camera(myCamera, car, CAMERA_STATE_SURVEILLANCE);
				current_camera = CAMERA_STATE_SURVEILLANCE;
			}

			/**SWITCH THE CAMERA  STATE CONTROLLS ENDS**/

			/*Reset orientation and position of current camera*/
			if (myEngine->KeyHit(Key_C)) {
				change_camera(myCamera, car, current_camera);
			}
		}
		/***CAMERAS SECTION ENDS***/
	}
}
