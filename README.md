Qt5 GL Test
======

This is a very simple application that creates a window and executes some pointless GL commands.

It is intended to demonstrate how certain OpenGL functions are working on amd64 systems
but will not even compile on armhf.

Simple Dockerfiles are provided that create environments that illustrate the compilation problem.

### amd64

```bash
sudo docker build -f Dockerfile.amd64 .
```

Observe how the application builds cleanly.

### armhf

```bash
sudo docker build -f Dockerfile.armhf .
```

Observe how compilation fails due to many missing OpenGL symbols.
