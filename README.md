## Invaders - Arduino

##### This is a game inspired from (and similar with) Chicken Invaders, playable on an Arduino Uno.

### Components
    1. 1x Arduino Uno
    2. ~32x jumper
    3. 2x buzzer (1x passive, 1x active)
    4. 1x LCD 1602
    5. 1x Max 7219 Matrix / Driver
    6. 1x Joystick
    7. 1x 10µf / 5v capacitor
    8. 1x 104 ceramic capacitor
    9. 1c 220Ω resistor

### The application has the following modules:

    1. The welcome screen

    2. "Enter your name" part (which is shown when your game ends, and you have a place in the leaderboard)

    3. Main menu - where you have the following options:
        a) Start the game
        b) Go to settings
        c) See the Leaderboard
        d) Go to "How to play" section
        e) Go to the "About" section

    4. Settings:
        a) LCD:
            i) Update the contrast
            ii) Update the backlight
        b) Matrix:
            i) Update the contrast
       
        c) Level - increase/decrease
        
        d) Sounds - turn on/off


    5. The game :D

### The most important components of the application, besides simple reusable classes, like _LCD_, _Button_ and _Joystick_, are the following:

    1. The State
      This is an abstract class, used with the StateManager (see below),
        which helps to easily build the logic of the app around "states".

      It has 3 important methods:
        a) `setup`: the code that is ran by the StateManager when the state changes to this one
          (for example, attaching a handler to a button)

        b) `handle`: the logic that should be ran while in this state

        c) `cleanup`: usually, here we "undo" what we did in setup
          (for example, dettaching the handler from the button in step a) :P)


    2. The StateManager
      This is probably one of the most important building block of the application.
      The state manager is a class which helps a lot when it comes to, well, managing the current state of the app.
      
      Here, you can change the current state. When doing so, the StateManager:
        a) cleans up the previous state
        b) sets up the new state

      In the main loop of the application, we can call simply call stateManager.handle().

    3. The Delayer
      This doesn't have the best implementation at the moment (it uses millis), but it's a simple class
      which helps when you want to run a function only at some time intervals. i.e.:

      if (delayer.canRun()) { // if the function can run, the "lastCall" gets updated to millis()
         // code
      }

      This will be used in a looot of places.


    4. The Menu
      My initial thought was that, a good way to display data on the LCD is to have a simple _Menu_,
      that can be reused, and has a simple logic:
        a) You define the messages that you can see on the screen
        b) What should happen when you click on them (you can also not add handlers -> clicking on the message will do nothing)

      Behind the scenes, it has methods for scrolling through the messages, selecting an action, and so on.

### Game Engine

    The game engine, and the way we create units is inspired from my second homework for _Object Oriented Programming_, a course from my first year @ Uni.
    You can see how it works [here](https://github.com/qfl1ck32/Object-Oriented-Programming/tree/master/Homework%202).
    
    A simple explanation would be:
        1) We have `Units`. `Unit` is an abstract class, which implements logic for moving, dying, sending messages to another unit, e.t.c.., having `abstract methods` for `action` and `behaviour` (how the unit should act on a particular message).
        
        2) The `GameEngine` has a NxM matrix of pointers to units, `unitsMatrix`, and an array of pointers to (the same) units: `unitsArray`.
        When a unit is created, it's added in the matrix, at its specific coordinates, and in the array - at the next index.
        
        When the game runs, the engine is doing the following:
            a) Calling `action` on every unit
            b) Calling `react` on every unit (which basically consumes the messages)
            c) Checks for units that have `died` in that round, and, for every dead unit:
                i) it deletes the unit
                ii) removes it from the matrix & array
                
        3) A new feature on the Game Engine, which isn't found in the implementation I gave above, is the fact that we have a linked list of `PixelChange` objects,
        stored in the game engine.
        
        A `PixelChange` contains the coordinates, `x` and `y` and the `state` (a boolean, i.e. is the pixel on/off).
        
        The naming might be a bit off, and may need to be changed to something like `UnitPositionChange`.
        
        
        This list is _consumed_ by the:

### GraphicsEngine

    This is a simple class which implements one method - `renderChanges` - which takes a `linked list of PixelChanges` and renders the changes on a matrix,
    consuming them along the way.
    
### GameStatus

    This is yet another simple class, which has two methods - `displayHeader` and `show`.
    The first method is called once, when we start the game - and it displays, on the first line of an LCD, the... header: *Lvl Pts Time*;
    The second method, `show`, takes the current `score`, `number of lifes`, `level` and `timeSoFar` and renders this data on the second row of the LCD.
    
### States

    Most of the states are self explanatory, like `AboutMenuState`, `HowToPlayMenuState`, e.t.c.., where we setup the messages / handlers for the menu.
    
    A more interesting state would be `PlayingState`, which holds the logic for the whole game:
    
        1. play() - a method which runs a round of the game engine, renders the changes on the matrix / LCD and handles the death / winning of a round (calling a `switchToX` method).
        
        2. reset() - self explanatory :)

        3. updateScore() - which uses:
            1. the number of seconds left in the round
            2. the number of bullets that were shot
           in order to increase the current score
           
   and so on :)
    
    
### Important notes

    We are using char* everywhere. No Strings. Also, no array of strings / numbers is saved directly into memory - we're using PROGMEM.
    Whenever we need a string from PROGMEM, we can use `readStringFromPROGMEM()`. :)
