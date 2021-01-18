# Crimata GTK App

![Crimata](/resources/homepage.png?raw=true "Crimata")

A fontend for the Crimata Platform in C with using GTK for graphics.

This is a good repository to browse for anyone looking to learn basic GTK, Cairo (animation), networking, and/or audio buffering. There are practical examples about how to apply these concepts. FYI, this has never been tested on Windows.

## Intro
Crimata is a platform for writing voice-driven applications, meaning it is a digital assistant like Siri or Alexa. All of the major logic for getting this done happens on our company's backend. Therefore, any frontend for the platform only needs to record and playback audio in addition to any visualization that we want to happen. This app was our first crack at what a desktop frontend might look like for our platform.

In it's current configuration, the app will:
  1. Open and run a launch animation
  2. Listen for a human voice
  3. Send clips of your voice to a dummy backend (included)
  4. Display messages from the backend
  5. Visualize what is happening with basic animations.
  
## Getting Started
![Startup GIF](/resources/startup-anim.gif?raw=true "Startup GIF")

### Required libraries
[GTK](https://www.gtk.org/docs/getting-started/) and [PortAudio](http://files.portaudio.com/docs/v19-doxydocs/tutorial_start.html) need to be built for your environment.

### Build app
`cd app/core` then run `make all` to build and run Crimata.app bundle.  

## License
[MIT](https://choosealicense.com/licenses/mit/)
