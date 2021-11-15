# State Design Pattern Demo

This level is a demonstration of my implementation of the state design pattern described in Game Programming Patterns by Robert Nystrom.

The demo has been created using the Sumo Digital Playbuffer framework.

![StateDesignPattern](https://user-images.githubusercontent.com/54814522/141779119-cca8b0f6-9f9b-4eec-a74f-205abd85ed92.gif)

The state pattern in my demo flows as follows:
1. In the Update function in Player.cpp the HandleInput function for the current state is called
2. The HandleInput function returns a new state if the user input dictates that it should, e.g. in IdleState pressing space returns new JumpingState
3. If the HandleInput function returns a new state then the pointer to the current state is deleted and a pointer to the new state is assigned
4. The Enter function for the current state is then called, setting the sprite and any state specific data
5. The StateUpdate function is called on the current state, handling movement, collision and pickups

Each movement state has its own Enter, HandleInput and Update functions. There is one class per state and the left and right variations are handled within the same class, based on an int passed into the state constructor.

To play:
1. Download the code from GitHub
2. Open the StateDesignPattern.sln file
3. Click Local Windows Debugger to run the demo
