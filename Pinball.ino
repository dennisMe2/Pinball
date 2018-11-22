#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <WString.h>

#include "../sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/variants/standard/pins_arduino.h"
#include "Controller/ABController.h"
#include "Controller/BasicLedController.h"
#include "Controller/BoatController.h"
#include "Controller/PalmController.h"
#include "Controller/PostController.h"
#include "Controller/WheelController.h"
#include "Game/Game.h"
#include "Game/Player.h"
#include "Game/Sound.h"
#include "Led/BasicLed.h"
#include "Led/Display.h"
#include "Led/SmartLed.h"
#include "Logic/PortExpander.h"
#include "Logic/PortUser.h"
#include "Logic/Switch.h"
#include "Power/DelayedKickOut.h"
#include "Utils.h"

#define LED_PIN 6

#define CLK1 2
#define DIO1 3
#define CLK2 4
#define DIO2 5

#define CSportExpander 10

//uint8_t litPixel = 0;
unsigned int sw_count = 500;

SoftwareSerial softSerial(7, 8); // arduino RX, TX

Sound sound = Sound();

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

PalmController palm = PalmController();
BasicLedController dumbLeds = BasicLedController();

BasicLed rollover_100 = BasicLed(&strip, 0, RED);
BasicLed a = BasicLed(&strip, 1, WHITE);
BasicLed islandRight = BasicLed(&strip, 2, WHITE);
BasicLed topRightSideUpper = BasicLed(&strip, 3, WHITE);
BasicLed topRightSideLower = BasicLed(&strip, 4, WHITE);
BasicLed topLeftKicker = BasicLed(&strip, 5, WHITE);
BasicLed rightSideUpper = BasicLed(&strip, 6, WHITE);
BasicLed bottomLeftKicker = BasicLed(&strip, 7, WHITE);
SmartLed palmTree1 = SmartLed(&strip, 8, GREEN);
SmartLed palmTree2 = SmartLed(&strip, 9, GREEN);
SmartLed palmTree3 = SmartLed(&strip, 10, GREEN);
SmartLed palmTree4 = SmartLed(&strip, 11, YELLOW);
SmartLed palmTree10x = SmartLed(&strip, 12, RED);
BasicLed b = BasicLed(&strip, 13, WHITE);
BasicLed islandLeft = BasicLed(&strip, 14, WHITE);
BasicLed topLeftSideUpper = BasicLed(&strip, 15, WHITE);
BasicLed topLeftSideLower = BasicLed(&strip, 16, WHITE);
BasicLed topRightKicker = BasicLed(&strip, 17, WHITE);
BasicLed bottomRightKicker = BasicLed(&strip, 18, WHITE);
BasicLed leftSideUpper = BasicLed(&strip, 19, WHITE);
BasicLed leftSideLower = BasicLed(&strip, 20, WHITE);

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

BasicLed rightSideLower = BasicLed(&strip, 32, WHITE);
BasicLed rightKickerUpper = BasicLed(&strip, 33, WHITE);
BasicLed red = BasicLed(&strip, 37, RED);
BasicLed blue = BasicLed(&strip, 36, BLUE);
BasicLed green = BasicLed(&strip, 35, GREEN);
BasicLed yellow = BasicLed(&strip, 34, YELLOW);
BasicLed leftSideKickerUpper = BasicLed(&strip, 38, WHITE);
BasicLed leftSideKickerLower = BasicLed(&strip, 39, WHITE);
BasicLed samePlayerShoots = BasicLed(&strip, 40, WHITE);
BasicLed rightKickerLower = BasicLed(&strip, 41, WHITE);
BasicLed postUpper = BasicLed(&strip, 42, WHITE);
BasicLed postLower = BasicLed(&strip, 43, WHITE);

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

DelayedKickOut kickOutTop = DelayedKickOut(3500, 13);
Solenoid kickerTopLeft = Solenoid();
Solenoid kickerTopRight = Solenoid();
Solenoid kickerBottomLeft = Solenoid();
Solenoid kickerBottomRight = Solenoid();
DelayedKickOut kickOutLeft = DelayedKickOut(7000, 17);
DelayedKickOut kickOutRight = DelayedKickOut(7000, 17);
Solenoid postUp = Solenoid();
Solenoid postDown = Solenoid();
Solenoid replayGate = Solenoid(255);
Solenoid ballChute = Solenoid();
Solenoid spare = Solenoid();
Solenoid tilt = Solenoid(0); // normally on!

BoatController boat = BoatController(&yellow, &green, &blue, &red);
WheelController wheel = WheelController(&boat);
ABController abController = ABController(&a, &b, &topLeftKicker,
		&topRightKicker, &bottomLeftKicker, &bottomRightKicker);
PostController post = PostController(&postUpper, &postLower, &postUp,
		&postDown);

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

	wheel.addLed10(&wheelCenter);
	wheel.setGame(&game);

	palm.addLed(&palmTree1, 0, 1);
	palm.addLed(&palmTree2, 1, 1);
	palm.addLed(&palmTree3, 2, 1);
	palm.addLed(&palmTree4, 3, 1);
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

	if (!sound.begin(softSerial)) { //Use softwareSerial to communicate with mp3.
		Serial.println(F("Unable to use MP3:"));
		Serial.println(F("Please insert the SD card!"));
	}

	sound.volume(30);
	sound.play(FOG_HORN);

	dispScore.setBrightness(0x02);
	dispScore.setGame(&game);

	dispGame.setBrightness(0x02);
	dispGame.setGame(&game);

	tilt.activate();
	Serial.println(F("End Of Boot phase"));
	delay(100);  //prime switch debounce counters;

	pinMode((unsigned char) A0, OUTPUT);
	digitalWrite((unsigned char) A0, LOW);
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
	sound.play(SOUND_COIN_IN);
}


unsigned char getPulse() {
	static bool pinHigh = false;
	pinHigh = !pinHigh;
	if (pinHigh == true) {
		return HIGH;
	}
	return LOW;
}

void loop() {
	static unsigned long loopTime, ballLaunched;

	digitalWrite((unsigned char) A0, getPulse()); //used to measure the actual loop timings using a scope
	loopTime = millis();

	//start by getting the latest switch input values
	switchBank1.refreshInputs();
	switchBank2.refreshInputs();

	testMode = isTestModeRequested(testMode);

	if ((game.getState() == RESET)) {
		dumbLeds.changeColors(CYAN);
		if (!sw_coinIn.getStatus()) {
			game.resetHighScore();
		}

		// EXIT CURRENT STATE BELOW HERE
		game.setState(LOCATE_BALL);

	} else if ((game.getState() == LOCATE_BALL) || testMode) {
		if ((loopTime - nextActivationTime) > 500) {
			switch (testCounter) {
			case 0:
				post.postDown();
				kickOutTop.activateImmediate();
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
				kickOutLeft.activateImmediate();
				break;
			case 6:
				kickOutRight.activateImmediate();
				break;
			case 7: //the port pin firing order is switched here so you can see if the mechanicals are in order
				post.postUp();
				break;
			case 8: //the port pin firing order is switched here so you can see if the mechanicals are in order
					//Port B
				post.postDown();
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
			// EXIT CURRENT STATE BELOW HERE
			if (++testCounter > 12) {
				testCounter = 0;
				game.setState(GAME_OVER);
			}
			nextActivationTime = loopTime;
		}

	} else if (game.getState() == GAME_OVER) {
		dumbLeds.changeColors(BLUE);
		game.resetPlayers();
		palm.setDelay(300); //fast animation
		palm.startAnimation();
		sound.play(AMBIENT_BOAT);

		wheel.setDelay(150);
		tilt.deactivate();

		dispScore.setFunction(SHOW_INSERT_COIN);
		dispGame.setFunction(SHOW_HIGH_SCORE);

		// EXIT CURRENT STATE BELOW HERE
		//adding a coin adds a player; max = 4 once a game starts no players can be added
		if (sw_coinIn.triggered()) {
			dispScore.setFunction(SHOW_NEXT_UP);
			ballChute.activate();
			ballLaunched = loopTime;
			game.setState(COIN_IN);
			addPlayer();
		}

	} else if (game.getState() == COIN_IN) {
		dumbLeds.changeColors(YELLOW);
		dispGame.setFunction(SHOW_PLAYER);
		dispScore.setFunction(SHOW_NUM_PLAYERS);

		if (sw_coinIn.triggered()) {
			addPlayer();
		}

		if (!sw_ballChute.getStatus()) {
			ballChute.activate();
			ballLaunched = loopTime;
		}

		// EXIT CURRENT STATE BELOW HERE
		//Shooting a ball immediately starts player 1's game with however many players were added
		if (!sw_ballRelease.getStatus() && ((loopTime - ballLaunched) > 1500)) {
			game.setState(FIRST_PLAYER_UP);
		}

	} else if (game.getState() == FIRST_PLAYER_UP) {
		// EXIT CURRENT STATE BELOW HERE
		game.setState(BEFORE_PLAY);

	} else if (game.getState() == PLAY_AGAIN) { //immediate replay without loss of achievements
		ballChute.activate();

		// EXIT CURRENT STATE BELOW HERE
		game.setState(PLAYER_PLAYING); // AUTO

	} else if (game.getState() == PLAYER_UP) {
		tilt.deactivate();
		dumbLeds.changeColors(GREEN);
		dispGame.setFunction(SHOW_PLAYER);
		dispScore.setFunction(SHOW_NEXT_UP);
		sound.play(AMBIENT_WAVES);

		// EXIT CURRENT STATE BELOW HERE
		if (sw_coinIn.triggered()) {
			ballChute.activate();
			game.setState(BEFORE_PLAY);
		}

	} else if (game.getState() == BEFORE_PLAY) {
		abController.reset();
		wheel.reset();
		boat.allOff();
		palm.ledsOff();
		dumbLeds.changeColors(MAGENTA);
		if (sw_ballChute.triggered())
			ballChute.activate();

		// EXIT CURRENT STATE BELOW HERE
		if (!sw_ballRelease.getStatus())
			post.postDown();
		game.setState(PLAYER_PLAYING);

	} else if (game.getState() == PLAYER_PLAYING) { //GAME ON!
		wheel.setDelay(1500);
		palm.stopAnimation();
		dumbLeds.changeColors(WHITE);

		dispGame.setFunction(SHOW_PLAYER_UP);
		dispScore.setFunction(SHOW_SCORE);

		game.setMultiplier(1);

		if (game.getReplay()) {
			samePlayerShoots.setColor(RED);
		} else {
			samePlayerShoots.setColor(BLACK);
		}

		tilt.activate();

		if (sw_rollOver_100.triggered()) {
			game.addScore(100);
			sound.play(CHIME_MED);
		}

		else if (sw_rollOverA.triggered()) {
			abController.setA();
			sound.play(CHIME_LOW);
		}

		else if (sw_rollOverB.triggered()) {
			abController.setB();
			sound.play(CHIME_LOW);
		}

		else if (sw_targetA.triggered()) {
			sound.play(CHIME_LOW);
			(abController.isSetA()) ? game.addScore(100) : game.addScore(10);
		}

		else if (sw_targetB.triggered()) {
			sound.play(CHIME_LOW);
			(abController.isSetB()) ? game.addScore(100) : game.addScore(10);
		}

		else if (sw_targetPostUpLeft.triggered()
				|| sw_targetPostUpRight.triggered()) {
			post.postUp();
			sound.play(CHIME_LOW);
		}

		else if (sw_targetPostDownLeft.triggered()
				|| sw_targetPostDownRight.triggered()) {
			post.postDown();
			game.addScore(30);
		}

		//a bunch of one point switches
		else if (sw_islandLeftTop.triggered() || sw_islandLeftBottom.triggered()
				|| sw_islandRightTop.triggered()
				|| sw_islandRightBottom.triggered() || sw_sideLeft.triggered()
				|| sw_sideRight.triggered()) {
			game.addScore(1);
			post.postDown();
			sound.play(CHIME_HIGH);
		}

		else if (sw_kickOutTop.triggered() && !kickOutTop.isInUse()) {
			kickOutTop.activate();
			palm.increment();
			game.addScore(palm.getMultiplier() * 50);
		}

		else if (sw_kickerTopLeft.triggered()) {
			sound.play(CHIME_LOW);
			game.addScore(
					palm.getMultiplier() * (abController.isSetB()) ? 10 : 1);
			kickerTopLeft.activate();
		}

		else if (sw_kickerTopRight.triggered()) {
			sound.play(CHIME_LOW);
			kickerTopRight.activate();
			game.addScore(
					palm.getMultiplier() * (abController.isSetA()) ? 10 : 1);
		}

		else if (sw_kickerBottomRight.triggered()) {
			sound.play(CHIME_LOW);
			game.addScore(
					palm.getMultiplier() * (abController.isSetB()) ? 10 : 1);
			kickerBottomRight.activate();
		}

		else if (sw_kickerBottomLeft.triggered()) {
			sound.play(CHIME_LOW);
			game.addScore(
					palm.getMultiplier() * (abController.isSetA()) ? 10 : 1);
			kickerBottomLeft.activate();
		}

		else if (sw_kickOutLeft.triggered() && !kickOutLeft.isInUse()) {
			game.addScore(wheel.getPoints());
			kickOutLeft.activate();
		}

		else if (sw_kickOutRight.triggered() && !kickOutRight.isInUse()) {
			game.addScore(wheel.getPoints());
			kickOutRight.activate();
		}

		else if (sw_rollOverPassRight.triggered()) {
			game.addScore(wheel.getPoints());
			sound.play(BELL_LOW);
			if (abController.isSetA() && abController.isSetB())
				replayGate.activate();
		}

		else if (sw_rollOverPassLeft.triggered()) {
			game.addScore(wheel.getPoints());
			sound.play(BELL_LOW);
		}

		// EXIT CURRENT STATE BELOW HERE
		//someone banged the board, big trouble!
		if (sw_tilt.triggered()) {  //TO TILT STATE
			game.setMultiplier(0);
			game.setState(TILT);
			post.postDown();
			sound.play(FOG_HORN);
		}

		//player lost ball; continue with next player or game over
		// this long switch wire is prone to picking up spikes which abruptly end a game,
		//so we handle it differently because response time is not important here
		if (!sw_ballChute.getStatus()) {
			if (--sw_count == 0) {
				game.lostBall(); //STATE: NEW_HISCORE_GAMEOVER || NEW_HISCORE_NEXT_PLAYER ||GAME_OVER
				post.postDown();
				sw_count = 500;
			}
		} else {
			sw_count = 500;
		}

	} else if (game.getState() == TILT) {
		palm.stopAnimation();
		tilt.deactivate();
		dumbLeds.changeColors(RED);

		//important ball doesn't end up hanging in a kickout forever
		if (sw_kickOutTop.triggered()) {
			kickOutTop.activateImmediate();
		}

		if (sw_kickOutLeft.triggered()) {
			kickOutLeft.activateImmediate();
		}

		if (sw_kickOutRight.triggered()) {
			kickOutRight.activateImmediate();
		}

		// EXIT CURRENT STATE BELOW HERE
		if (sw_ballChute.triggered()) {
			game.lostBall(); //STATE: NEW_HISCORE_GAMEOVER || NEW_HISCORE_NEXT_PLAYER ||GAME_OVER
		}

	} else if (game.getState() == NEW_HISCORE_GAMEOVER) {
		dispGame.setFunction(SHOW_HISCORE_PLAYER);
		dispScore.setFunction(SHOW_HIGH_SCORE);
		sound.play(TUNE_HISCORE);

		// EXIT CURRENT STATE BELOW HERE
		if (sw_coinIn.triggered()) {
			game.setState(GAME_OVER);
		}
	} else if (game.getState() == NEW_HISCORE_NEXT_PLAYER) {
		dispGame.setFunction(SHOW_HISCORE_PLAYER);
		dispScore.setFunction(SHOW_HIGH_SCORE);
		sound.play(TUNE_HISCORE);

		// EXIT CURRENT STATE BELOW HERE
		if (sw_coinIn.triggered()) {
			game.setState(PLAYER_UP);
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
