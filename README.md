## Chicken Invaders - Arduino


##### This is a simulation of Chicken Invaders, playable on an Arduino Uno.

### The application has, *for the moment*, the following modules:

    1. The welcome screen
    
    2. "Enter your name" part
      (which may be moved in the future, I intend to show it only when you get a place in the Leaderboard)
      
    3. Main menu - where you have the following options:
        a) Start the game
        b) Go to settings
        c) See the Leaderboard
        d) Go to the "About" section
        
    4. Settings:
        a) Update the contrast
        b) Update the backlight
        
        
    5. The game :D
    
### The most important components of the application, besides simple reusable classes, like _LCD_, _Button_ and _Joystick_, are the following:

      
    1. The State
      This is an abstract class, used with the StateManager (see below),
        which helps to easily build the logic of the app around "states".
        
      It has an id, which we pass to it in the constructor, and 3 important methods:
        a) `setup`: the code that is ran by the StateManager when the state changes to this one
          (for example, attaching a handler to a button)
          
        b) `handle`: the logic that should be ran while in this state
        
        c) `cleanup`: usually, here we "undo" what we did in setup
          (for example, dettaching the handler from the button in step a) :P)
      
      
    2. The StateManager
      This is probably one of the most important pieces of the application.
      The state manager is a class which helps a lot when it comes to, well, managing the current state of the app.
      It works in the following way:
        
        1) You can add a new state
        2) You can change the state, given a stateId.
        
      When changing the state, the StateManager:
        a) cleans up the previous state
        b) sets up the new state
        
      In the main loop of the application, we can call simply call stateManager->handle().

    3. The Delayer
      This doesn't have the best implementation at the moment (it uses millis), but it's a simple class
      which helps when you want to run a function only at some time intervals. i.e.:
      
      if (delayer.canRun()) { // if the function can run, the "lastCall" gets updated to millis()
         // code
      }
      
      This will be used in a looot of places.
      
      
    4. The Menu
      My initial thought that, a good way to display data on the LCD is to have a simple _Menu_,
      that can be reused, and has a simple logic:
        a) You define the messages that you can see on the screen
        b) What should happen when you click on them
        
      Behind the scenes, it has methods for scrolling through the messages, selecting an action, and so on.
      
##### To be continued :)
      

      
