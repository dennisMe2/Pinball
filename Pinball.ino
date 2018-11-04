#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Display.h"
#include "SmartLed.h"
#include "LedWheelController.h"
#include "LedPalmController.h"
#include "PortExpander.h"
#include "Solenoid.h"
#include "DelayedKickOut.h"
#include "Switch.h"
#include "Game.h"
#include "Player.h"
#include "utils.h"

#define LED_PIN 6

//primary & complementary color wheel:
#define RED 255,0,0
#define YELLOW 255,255,0
#define GREEN 0,255,0
#define CYAN 0,255,255
#define BLUE 0,0,255
#define MAGENTA 255,0,255
#define WHITE 255,255,255
#define BLACK 0,0,0
#define GREY 127,127,127

#define CLK1 2
#define DIO1 3
#define CLK2 4
#define DIO2 5

#define CSportExpander 10

uint8_t litPixel = 0;
unsigned int loopTime = 0;

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

unsigned int nextLedUpdate = 0;
uint8_t ledUpdateDelay = 100;

PortExpander driverBank = PortExpander(&SPI, CSportExpander, 0);
PortExpander switchBank1 = PortExpander(&SPI, CSportExpander, 1);
PortExpander switchBank2 = PortExpander(&SPI, CSportExpander, 3);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(44, LED_PIN,
NEO_RGB + NEO_KHZ800);

LedWheelController wheel = LedWheelController();
LedPalmController palm = LedPalmController();

SmartLed rollover_100 = SmartLed(&strip, 0, RED);
SmartLed b = SmartLed(&strip, 1);
SmartLed islandRight = SmartLed(&strip, 2);
SmartLed topRightSideUpper = SmartLed(&strip, 3);
SmartLed topRightSideLower = SmartLed(&strip, 4);
SmartLed topRightKicker = SmartLed(&strip, 5);
SmartLed rightSideUpper = SmartLed(&strip, 6);
SmartLed bottomRightKicker = SmartLed(&strip, 7);
SmartLed palmTree1 = SmartLed(&strip, 8, GREEN);
SmartLed palmTree2 = SmartLed(&strip, 9, GREEN);
SmartLed palmTree3 = SmartLed(&strip, 10, GREEN);
SmartLed palmTree4 = SmartLed(&strip, 11, YELLOW);
SmartLed palmTree10x = SmartLed(&strip, 12, RED);
SmartLed a = SmartLed(&strip, 13);
SmartLed islandLeft = SmartLed(&strip, 14);
SmartLed topLeftSideUpper = SmartLed(&strip, 15);
SmartLed topLeftSideLower = SmartLed(&strip, 16);
SmartLed topLeftKicker = SmartLed(&strip, 17);
SmartLed bottomLeftKicker = SmartLed(&strip, 18);
SmartLed leftSideUpper = SmartLed(&strip, 19);
SmartLed leftSideLower = SmartLed(&strip, 20);

SmartLed wheelNorth = SmartLed(&strip, 21, BLUE);
SmartLed wheelCenter = SmartLed(&strip, 22, BLUE);
SmartLed wheelNNW = SmartLed(&strip, 23, BLUE);
SmartLed wheelWNW = SmartLed(&strip, 24, BLUE);
SmartLed wheelWSW = SmartLed(&strip, 25, BLUE);
SmartLed wheelSSW = SmartLed(&strip, 26, BLUE);
SmartLed wheelSouth = SmartLed(&strip, 27, BLUE);
SmartLed wheelSSE = SmartLed(&strip, 28, BLUE);
SmartLed wheelESE = SmartLed(&strip, 29, BLUE);
SmartLed wheelENE = SmartLed(&strip, 30, BLUE);
SmartLed wheelNNE = SmartLed(&strip, 31, BLUE);

SmartLed rightSideLower = SmartLed(&strip, 32);
SmartLed rightKickerUpper = SmartLed(&strip, 33);
SmartLed red = SmartLed(&strip, 34, RED);
SmartLed blue = SmartLed(&strip, 35, BLUE);
SmartLed green = SmartLed(&strip, 36, GREEN);
SmartLed yellow = SmartLed(&strip, 37, YELLOW);
SmartLed leftSideKickerUpper = SmartLed(&strip, 38);
SmartLed leftSideKickerLower = SmartLed(&strip, 39);
SmartLed samePlayerShoots = SmartLed(&strip, 40, RED);
SmartLed rightKickerLower = SmartLed(&strip, 41);
SmartLed postUpper = SmartLed(&strip, 42, RED);
SmartLed postLower = SmartLed(&strip, 43, RED);

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
Solenoid replayGate = Solenoid(1000);
DelayedKickOut ballChute = DelayedKickOut(3000);
Solenoid spare = Solenoid();
Solenoid tilt = Solenoid(0); // normally on!

void setup() {
	Serial.begin(9600);
	randomSeed(analogRead(0));

	wheel.addLed(&wheelNNW, 0);
	wheel.addLed(&wheelWNW, 1);
	wheel.addLed(&wheelWSW, 2);
	wheel.addLed(&wheelSSW, 3);
	wheel.addLed(&wheelSouth, 4);
	wheel.addLed(&wheelSSE, 5);
	wheel.addLed(&wheelESE, 6);
	wheel.addLed(&wheelENE, 7);
	wheel.addLed(&wheelNNE, 8);
	wheel.addLed(&wheelNorth, 9);

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
	driverBank.addSolenoid(&postDown, 7);
	//Port B
	driverBank.addSolenoid(&postUp, 8);
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

	softSerial.begin(9600);

	strip.begin();
	strip.setBrightness(255);
	// https://www.tweaking4all.nl/hardware/arduino/arduino-ws2812-led/
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

	tilt.deactivate();
	Serial.println(F("End Of Boot phase"));
}

bool testMode = true;
uint8_t testCounter = 0;
unsigned int nextActivationTime = 0;

void loop() {
	loopTime = intMillis();

	if(testMode && (loopTime > nextActivationTime)){


		switch (testCounter){
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
		case 7://the port pin firing order is switched here so you can see if the mechanicals are in order
				postUp.activate();
				break;
		case 8://the port pin firing order is switched here so you can see if the mechanicals are in order
				//Port B
				postDown.activate();
				break;
		case 9:
				replayGate.activate();
				break;
		case 10:
			ballChute.activateDelayed();
				break;
		case 11:
				spare.activate();
				break;
		case 12://you may want to hold a flipper for this one!
				tilt.activate();
				break;
		}

		if(++testCounter > 12) testCounter = 0;

		nextActivationTime = loopTime + 1000;
	}

	//start by getting the latest switch input values
	switchBank1.refreshInputs();
	switchBank2.refreshInputs();

	//Game over behavior, add players, start game, advertise etc
	if (!testMode && game.isGameOver()) {
		palm.setDelay(300); //fast animation
		wheel.setDelay(150);

		if(game.getNumPlayers() == 0){
			dispGame.showInsertCoin();
			dispScore.showInsertCoin();
		}

		tilt.deactivate();
		//adding a coin adds a player; max = 4 once a game starts no players can be added
		if (sw_coinIn.triggered()) {
			game.addPlayer();
			dispGame.showPlayer();
			dispScore.showNumPlayers();
			ballChute.activate();
		}

		//Shooting a ball immediately starts player 1's game with however many players were added
		if ((game.getNumPlayers() > 0) && (sw_ballRelease.triggered() )) {

			game.playBall();
			dispGame.showPlayer();
		}

		//might want to randomly make some noise too!
		//   or maybe not...

	} else if(! testMode){ //GAME ON!
		palm.setDelay(1500); //slower animation
		wheel.setDelay(2500);

		dispGame.showPlayerUp();
		dispScore.showScore();

		tilt.activate();

		//dumbass player lost ball, continue with next player or game over
		if (sw_ballChute.triggered()) {
			game.lostBall();
			ballChute.activate();
		}

		//someone banged the board, big trouble!
		if (sw_tilt.triggered()) {
			postDown.activate();
			tilt.deactivate();
			mP3.play(1);
		}

		if (sw_targetA.triggered() || sw_targetB.triggered()) {
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

	}

	palm.animate();
	wheel.animate();

	// end of cycle tasks, refreshing i/o and displays etc
	driverBank.refreshOutputs();

	//don't update the LEDs too quickly to save precious milliseconds
	if(loopTime > nextLedUpdate ){
		strip.show();	//Duration  = 1.3 ms!
		nextLedUpdate = loopTime + ledUpdateDelay;
	}

	dispScore.refreshDisplay();
	dispGame.refreshDisplay();

	switchBank1.resetTriggers();
	switchBank2.resetTriggers();
}
