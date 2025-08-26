#  Clear Cut
<br>

Clear Cut is a simple platformer game where you play as an agent of a loggin company. Your one goal is the make the shareholder happy, and they love when you shoot down trees. If you don’t kill a tree/plant every 30 seconds, the shareholders will pull their funding and the game will end, but be careful because this forest fights back. 

As the player progresses through the game and facing different enemies, fewer and fewer trees appear, the background becomes increasingly sparse, and the theme music becomes stripped back. Eventually, there are no more trees to cut down...but the shareholders still demand more. At the end, you are forced to sit there and wait until they pull their funding, ending the game.

<br>

## How It's Made
<br> 
This game was originally written in Processing before being ported over to C++ within the SFML framework. Modern C++ was strongly kept in mind in this port, using stl containers, templates, etc. 
All the art for this game was developed in various online pixel art applications, which can account for differently sized and shaded pixels. All the music was either composed or recorded myself and was played back using the SFML audio library.

<br>

## Lessons Learned
<br>
Look, the architecture of this game is rough. It was originally written in Processing using plenty of globals and little regard for memory safety. Porting it over to C++ has been an incredible learning experience for two reasons. First, it has helped me further practice my C++ outside of an Audio DSP context (which is a bit more my wheelhouse) and second, I have learned so many important lessons about game dev. While these things may seem simple to a more experience game dev, here are just a few things I did not implement in this game that I fully intend to utilize going forward.

<br>

1. Give each entity it's own hit box, which is used for collision detection and seperate from the sprite. Collision detection and enemy/npc AI is a HUGE topic to explore!
2. Make sure sprite art sheets are formatted correctly and normally --> use Asesprite of photoshop. Make sure all assets are well organized
3. Scenes! There's gotta be a better way to select the start/game/gameover screens without shoving all the main game movements into one huge function...this function is...rough. Packaging scenes up into unique classes provides good memory control along with unique parameters for each scene.
4. Use middleware like FMOD to fine tune audio. High quality sounds really elevate the gaming experience.
5. Allocating class objects within stl containers is useful for packaging them, but these containers change memory addresses for their members as objects are included/popped, so just be careful. Use sprite batches, group update functions, static member functions/variables, and other tools that may be better suited for grouping class objects!

<br>
These changes, among many more, can be implemented in this game to optimize it, but frankly, Clear Cut is a fun little proof of concept, nothing more. It works smoothly for me, which is enough right now. I would rather work on the plethora of ideas I have stored up and make something new!


## Build & Play
<br>



