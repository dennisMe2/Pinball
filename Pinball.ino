#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Display.h"
#include "SmartLed.h"
#include "DumbLed.h"
#include "LedWheelController.h"
#include "LedPalmController.h"
#include "PortExpander.h"
#include "Solenoid.h"
#include "DelayedKickOut.h"
#include "Switch.h"
#include "Game.h"
#include "Player.h"
#include "Utils.h"
#include "DumbLedController.h"
#include "BoatController.h"

#define LED_PIN 6

#define CLK1 2
#define DIO1 3
#define CLK2 4
#define DIO2 5

#define CSportExpander 10

uint8_t litPixel = 0;
unsigned long loopTime = 0;

SoftwareSerial softSerial(7, 8); // arduino RX, TX
DFRobotDFPlayerMini mP3;

Display dispScore(CLK1, DIO1);
Display dispGame(CLK2, DIO2);

//For memory management reasons the max number of players must be predefined.
Player player1 = Player();
Player player2 = Player();
Player player3 = Player();
Player player4 = Player();

Game game = Game(3, &player1, &player2, &player3, &player4);

unsigned long nextLedUpdate = 0;
uint8_t ledUpdateDelay = 100;

PortExpander driverBank = PortExpander(&SPI, CSportExpander, 0);
PortExpander switchBank1 = PortExpander(&SPI, CSportExpander, 1);
PortExpander switchBank2 = PortExpander(&SPI, CSportExpander, 3);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(44, LED_PIN,
NEO_RGB + NEO_KHZ800);


LedPalmController palm = LedPalmController();
DumbLedController dumbLeds = DumbLedController();

DumbLed rollover_100 = DumbLed(&strip, 0, WHITE);
DumbLed b = DumbLed(&strip, 1, WHITE);
DumbLed islandRight = DumbLed(&strip, 2, WHITE);
DumbLed topRightSideUpper = DumbLed(&strip, 3, WHITE);
DumbLed topRightSideLower = DumbLed(&strip, 4, WHITE);
DumbLed topRightKicker = DumbLed(&strip, 5, WHITE);
DumbLed rightSideUpper = DumbLed(&strip, 6, WHITE);
DumbLed bottomRightKicker = DumbLed(&strip, 7, WHITE);
SmartLed palmTree1 = SmartLed(&strip, 8, GREEN);
SmartLed palmTree2 = SmartLed(&strip, 9, GREEN);
SmartLed palmTree3 = SmartLed(&strip, 10, GREEN);
SmartLed palmTree4 = SmartLed(&strip, 11, YELLOW);
SmartLed palmTree10x = SmartLed(&strip, 12, RED);
DumbLed a = DumbLed(&strip, 13, WHITE);
DumbLed islandLeft = DumbLed(&strip, 14, WHITE);
DumbLed topLeftSideUpper = DumbLed(&strip, 15, WHITE);
DumbLed topLeftSideLower = DumbLed(&strip, 16, WHITE);
DumbLed topLeftKicker = DumbLed(&strip, 17, WHITE);
DumbLed bottomLeftKicker = DumbLed(&strip, 18, WHITE);
DumbLed leftSideUpper = DumbLed(&strip, 19, WHITE);
DumbLed leftSideLower = DumbLed(&strip, 20, WHITE);

SmartLed wheelNorth = SmartLed(&strip, 21, RED);
SmartLed wheelCenter = SmartLed(&strip, 22, WHITE);
SmartLed wheelNNW = SmartLed(&strip, 23, YELLOW);
SmartLed wheelWNW = SmartLed(&strip, 24, GREEN);
SmartLed wheelWSW = SmartLed(&strip, 25, BLUE);
SmartLed wheelSSW = SmartLed(&strip, 26, RED);
SmartLed wheelSouth = SmartLed(&strip, 27, YELLOW);
SmartLed wheelSSE = SmartLed(&strip, 28, GREEN);
SmartLed wheelESE = SmartLed(&strip, 29, BLUE);
SmartLed wheelENE = SmartLed(&strip, 30, RED);
SmartLed wheelNNE = SmartLed(&strip, 31, YELLOW);

DumbLed rightSideLower = DumbLed(&strip, 32, WHITE);
DumbLed rightKickerUpper = DumbLed(&strip, 33, WHITE);
DumbLed red = DumbLed(&strip, 37, RED);
DumbLed blue = DumbLed(&strip, 36, BLUE);
DumbLed green = DumbLed(&strip, 35, GREEN);
DumbLed yellow = DumbLed(&strip, 34, YELLOW);
DumbLed leftSideKickerUpper = DumbLed(&strip, 38, WHITE);
DumbLed leftSideKickerLower = DumbLed(&strip, 39, WHITE);
DumbLed samePlayerShoots = DumbLed(&strip, 40, WHITE);
DumbLed rightKickerLower = DumbLed(&strip, 41, WHITE);
DumbLed postUpper = DumbLed(&strip, 42, WHITE);
DumbLed postLower = DumbLed(&strip, 43, WHITE);

Switch sw_rollOver_100 = Switch();
Switch sw_rollOverA = Switch();
Switch sw_rollOverB = Switch();
Switch sw_islandLeftTop = Switch();
Switch sw_islandLeftBottom = Switch();
Switch sw_islandRightTop = Switch();
Switch sw_islandRightBottom = Switch();
Switch sw_kickOutTop = Switch();
Switch sw_targetA = Switch();
Switch sw_targetB = Switch();
Switch sw_kickerTopLeft = Switch();
Switch sw_kickerTopRight = Switch();
Switch sw_kickerBottomLeft = Switch();
Switch sw_kickerBottomRight = Switch();
Switch sw_sideLeft = Switch();
Switch sw_sideRight = Switch();

Switch sw_targetPostUpLeft = Switch();
Switch sw_targetPostUpRight = Switch();
Switch sw_kickOutLeft = Switch();
Switch sw_kickOutRight = Switch();
Switch sw_targetPostDownLeft = Switch();
Switch sw_targetPostDownRight = Switch();
Switch sw_tilt = Switch();
Switch sw_rollOverPassLeft = Switch();
Switch sw_rollOverPassRight = Switch();
Switch sw_ballRelease = Switch();
Switch sw_ballChute = Switch();
Switch sw_coinIn = Switch();

DelayedKickOut kickOutTop = DelayedKickOut(3500);
Solenoid kickerTopLeft = Solenoid();
Solenoid kickerTopRight = Solenoid();
Solenoid kickerBottomLeft = Solenoid();
Solenoid kickerBottomRight = Solenoid();
DelayedKickOut kickOutLeft = DelayedKickOut(7000);
DelayedKickOut kickOutRight = DelayedKickOut(7000);
Solenoid postUp = Solenoid();
Solenoid postDown = Solenoid();
Solenoid replayGate = Solenoid(255);
Solenoid ballChute = Solenoid();
Solenoid spare = Solenoid();
Solenoid tilt = Solenoid(0); // normally on!

BoatController boat = BoatController(&yellow, &green, &blue, &red);
LedWheelController wheel = LedWheelController(&boat);

void setup() {
	Serial.begin(9600);
	randomSeed(analogRead(0));

	dumbLeds.addLed(&islandRight);
	dumbLeds.addLed(&topRightSideUpper);
	dumbLeds.addLed(&topRightSideLower);
	dumbLeds.addLed(&rightSideUpper);
	dumbLeds.addLed(&islandLeft);
	dumbLeds.addLed(&topLeftSideUpper);
	dumbLeds.addLed(&topLeftSideLower);
	dumbLeds.addLed(&leftSideUpper);
	dumbLeds.addLed(&leftSideLower);
	dumbLeds.addLed(&rightSideLower);
	dumbLeds.addLed(&rightKickerUpper);
	dumbLeds.addLed(&leftSideKickerUpper);
	dumbLeds.addLed(&leftSideKickerLower);
	dumbLeds.addLed(&rightKickerLower);

	wheel.addLed(&wheelNorth, 0);
	wheel.addLed(&wheelNNW, 1);
	wheel.addLed(&wheelWNW, 2);
	wheel.addLed(&wheelWSW, 3);
	wheel.addLed(&wheelSSW, 4);
	wheel.addLed(&wheelSouth, 5);
	wheel.addLed(&wheelSSE, 6);
	wheel.addLed(&wheelESE, 7);
	wheel.addLed(&wheelENE, 8);
	wheel.addLed(&wheelNNE, 9);



	palm.addLed(&palmTree1, 0, 1);
	palm.addLed(&palmTree2, 1, 2);
	palm.addLed(&palmTree3, 2, 3);
	palm.addLed(&palmTree4, 3, 4);
	palm.addLed(&palmTree10x, 4, 10);

	//Port A
	driverBank.addSolenoid(&kickOutTop, 0);
	driverBank.addSolenoid(&kickerTopLeft, 1);
	driverBank.addSolenoid(&kickerTopRight, 2);
	driverBank.addSolenoid(&kickerBottomLeft, 3);
	driverBank.addSolenoid(&kickerBottomRight, 4);
	driverBank.addSolenoid(&kickOutLeft, 5);
	driverBank.addSolenoid(&kickOutRight, 6);
	driverBank.addSolenoid(&postUp, 7);
	//Port B
	driverBank.addSolenoid(&postDown, 8);
	driverBank.addSolenoid(&replayGate, 9);
	driverBank.addSolenoid(&ballChute, 10);
	driverBank.addSolenoid(&spare, 11);
	driverBank.addSolenoid(&tilt, 12);
	driverBank.begin();

	//Port A
	switchBank1.addSwitch(&sw_rollOver_100, 0);
	switchBank1.addSwitch(&sw_rollOverA, 1);
	switchBank1.addSwitch(&sw_rollOverB, 2);
	switchBank1.addSwitch(&sw_islandLeftTop, 3);
	switchBank1.addSwitch(&sw_islandLeftBottom, 4);
	switchBank1.addSwitch(&sw_islandRightTop, 5);
	switchBank1.addSwitch(&sw_islandRightBottom, 6);
	switchBank1.addSwitch(&sw_kickOutTop, 7);
	//Port B
	switchBank1.addSwitch(&sw_targetA, 8);
	switchBank1.addSwitch(&sw_targetB, 9);
	switchBank1.addSwitch(&sw_kickerTopLeft, 10);
	switchBank1.addSwitch(&sw_kickerTopRight, 11);
	switchBank1.addSwitch(&sw_kickerBottomLeft, 12);
	switchBank1.addSwitch(&sw_kickerBottomRight, 13);
	switchBank1.addSwitch(&sw_sideLeft, 14);
	switchBank1.addSwitch(&sw_sideRight, 15);
	switchBank1.begin();

	//Port A
	switchBank2.addSwitch(&sw_targetPostUpLeft, 0);
	switchBank2.addSwitch(&sw_targetPostUpRight, 1);
	switchBank2.addSwitch(&sw_kickOutLeft, 2);
	switchBank2.addSwitch(&sw_kickOutRight, 3);
	switchBank2.addSwitch(&sw_targetPostDownLeft, 4);
	switchBank2.addSwitch(&sw_targetPostDownRight, 5);
	switchBank2.addSwitch(&sw_tilt, 6);
	switchBank2.addSwitch(&sw_rollOverPassLeft, 7);
	//Port B
	switchBank2.addSwitch(&sw_rollOverPassRight, 8);
	switchBank2.addSwitch(&sw_ballRelease, 9);
	switchBank2.addSwitch(&sw_ballChute, 10);
	switchBank2.addSwitch(&sw_coinIn, 11);
	switchBank2.begin();

	kickOutLeft.setWheelController(&wheel);
	kickOutRight.setWheelController(&wheel);

	softSerial.begin(9600);

	strip.begin();
	strip.setBrightness(255);
	strip.show();

	if (!mP3.begin(softSerial)) {  //Use softwareSerial to communicate with mp3.
		Serial.println(F("Unable to use MP3:"));
		Serial.println(F("Please insert the SD card!"));
	}

	mP3.volume(30);
	mP3.play(1);

	dispScore.setBrightness(0x02);
	dispScore.setGame(&game);

	dispGame.setBrightness(0x02);
	dispGame.setGame(&game);

	tilt.activate();
	Serial.println(F("End Of Boot phase"));
}

bool testMode = false;
int testModeCounter = 0;

uint8_t testCounter = 0;
unsigned long nextActivationTime = 0;

bool isTestModeRequested(bool testMode) {
	if (!sw_coinIn.getStatus()) {  //switch pushed
		if (++testModeCounter > 2000) {
			testMode = !testMode;
			testModeCounter = 0;
		}
	} else {
		testModeCounter = 0;
	}
	return testMode;
}

void addPlayer() {
	game.addPlayer();
	mP3.play(3);
}

void loop() {
	loopTime = millis();

	testMode = isTestModeRequested(testMode);

	//start by getting the latest switch input values
	switchBank1.refreshInputs();
	switchBank2.refreshInputs();

	if (testMode) {
		if (loopTime > nextActivationTime) {
			switch (testCounter) {
			case 0:
				kickOutTop.activateDelayed();
				break;
			case 1:
				kickerTopLeft.activate();
				break;
			case 2:
				kickerTopRight.activate();
				break;
			case 3:
				kickerBottomLeft.activate();
				break;
			case 4:
				kickerBottomRight.activate();
				break;
			case 5:
				kickOutLeft.activateDelayed();
				break;
			case 6:
				kickOutRight.activateDelayed();
				break;
			case 7: //the port pin firing order is switched here so you can see if the mechanicals are in order
				postUp.activate();
				break;
			case 8: //the port pin firing order is switched here so you can see if the mechanicals are in order
					//Port B
				postDown.activate();
				break;
			case 9:
				replayGate.activate();
				break;
			case 10:
				ballChute.activate();
				break;
			case 11:
				spare.activate();
				break;
			case 12:			//you may want to hold a flipper for this one!
				tilt.activate();
				break;
			}
		}
		if (++testCounter > 12)
			testCounter = 0;

		nextActivationTime = loopTime + 1000;
	} else if (game.getState() == GAME_OVER) {
		dumbLeds.changeColors(BLUE);

		palm.setDelay(300); //fast animation
		wheel.setDelay(150);
		tilt.deactivate();

		dispGame.showInsertCoin();
		dispScore.showInsertCoin();

		//adding a coin adds a player; max = 4 once a game starts no players can be added
		if (sw_coinIn.triggered()) {
			ballChute.activate();
			game.setState(COIN_IN);
			addPlayer();
		}

	} else if (game.getState() == COIN_IN) {
		dumbLeds.changeColors(YELLOW);

		if (sw_coinIn.triggered()) {
			addPlayer();
		}
		//Shooting a ball immediately starts player 1's game with however many players were added
		if (sw_ballRelease.triggered()) {
			game.setState(FIRST_PLAYER_UP);
		}

		dispGame.showPlayer();
		dispScore.showNumPlayers();

	} else if (game.getState() == FIRST_PLAYER_UP) {
		game.setState(PLAYER_PLAYING);

	} else if (game.getState() == PLAYER_UP) {
		tilt.deactivate();
		dumbLeds.changeColors(GREEN);
		dispGame.showPlayer();
		dispScore.showPlayer();

		if (sw_coinIn.triggered()) {
			ballChute.activate();
			game.setState(PLAYER_PLAYING);
		}

	} else if (game.getState() == PLAYER_PLAYING) { //GAME ON!
		//palm.setDelay(15000); //slower animation
		wheel.setDelay(1500);
		dumbLeds.changeColors(WHITE);

		dispGame.showPlayerUp();
		dispScore.showScore();

		tilt.activate();

		//player lost ball; continue with next player or game over
		if (sw_ballChute.triggered()) {
			game.lostBall();

		}

		if (sw_targetA.triggered() || sw_targetB.triggered()) {
			postUp.activate();
			game.addScore(10);
		}

		if (sw_targetPostUpLeft.triggered()
				|| sw_targetPostUpRight.triggered()) {
			postUp.activate();
			game.addScore(10);
		}

		if (sw_targetPostDownLeft.triggered()
				|| sw_targetPostDownRight.triggered()) {
			postDown.activate();
		}

		if (sw_islandLeftTop.triggered() || sw_islandLeftBottom.triggered()
				|| sw_islandRightTop.triggered()
				|| sw_islandRightBottom.triggered()) {
			game.addScore(1);
			postDown.activate();
		}

		if (sw_kickOutTop.triggered()) {
			kickOutTop.activate();
			game.addScore(10);
		}

		if (sw_kickerTopLeft.triggered()) {
			mP3.play(1);
			game.addScore(10);
			kickerTopLeft.activate();
		}

		if (sw_kickerTopRight.triggered()) {
			mP3.play(1);
			kickerTopRight.activate();
			game.addScore(10);
		}

		if (sw_kickerBottomRight.triggered()) {
			mP3.play(1);
			game.addScore(10);
			kickerBottomRight.activate();
		}

		if (sw_kickerBottomLeft.triggered()) {
			mP3.play(1);
			game.addScore(10);
			kickerBottomLeft.activate();
		}

		if (sw_kickOutLeft.triggered()) {
			game.addScore(10);
			kickOutLeft.activate();
		}

		if (sw_kickOutRight.triggered()) {
			game.addScore(10);
			kickOutRight.activate();
		}

		if (sw_rollOverPassRight.triggered()) {
			game.addScore(10);
			replayGate.activate();
		}

		//Set games score multiplier depending on the lit LEDs
		game.setMultiplier(palm.getMultiplier());

		//someone banged the board, big trouble!
		if (sw_tilt.triggered()) {
			game.setState(TILT);
			postDown.activate();
			mP3.play(2);
		}

	} else if (game.getState() == TILT) {
		tilt.deactivate();
		dumbLeds.changeColors(RED);

		if (sw_ballChute.triggered()) {
			game.lostBall();
		}

		//important ball doesn't end up hanging in a kickout forever
		if (sw_kickOutTop.triggered()) {
			kickOutTop.activateDelayed();
		}

		if (sw_kickOutLeft.triggered()) {
			kickOutLeft.activateDelayed();
		}

		if (sw_kickOutRight.triggered()) {
			kickOutRight.activateDelayed();
		}

	}

	palm.animate();
	wheel.animate();

	// end of cycle tasks, refreshing i/o and displays etc
	driverBank.refreshOutputs();

	//don't update the LEDs too quickly to save precious milliseconds
	if (loopTime > nextLedUpdate) {
		strip.show();	//Duration  = 1.3 ms!
		nextLedUpdate = loopTime + ledUpdateDelay;
	}

	if (!testMode) {
		dispScore.refreshDisplay();
		dispGame.refreshDisplay();
	} else {
		switchBank1.showPinsOn7Segment(&dispGame);
		switchBank2.showPinsOn7Segment(&dispScore);
	}

	switchBank1.resetTriggers();
	switchBank2.resetTriggers();

	game.update();
}
