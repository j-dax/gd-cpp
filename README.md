# C++ in godot 4.3

I started this project to explore programming a game in C++ using godot. Using the plugin system, everything can be done in C++. I did elect to do some things in the editor (i.e. hooking up signals to my c++ functions).

This repo roughly follows [this tutorial](https://docs.godotengine.org/en/4.3/getting_started/first_2d_game/) and was written when 4.3 was the stable version.

## Setup

Clone the repo and its submodules

`git clone --recurse-submodules -j8 git://github.com/foo/bar.git`

Run the compiler script

`scons`

(optional) If you want to use ccls, there's also an option to create the compile_commands.json directly

`scons compiledb`

Now you can open the `project/` directory in godot!

## Special Thanks

I found a nice resource in [this repo](https://github.com/nathanfranke/gdextension). Thank you @nathanfranke.
