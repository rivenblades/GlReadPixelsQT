# GlReadPixelsQT
I want to render opengl into a QImage.Want to use glfw and glew for opengl context &amp; extensions,not Qt's

# Before resizing, everything renders fine
![alt text](BeforeResizing.png)

# After resizing, image doesnt scale properly.Don't know if it is opengl's fault or qt's
![alt text](AfterResizing.png)

# Correct with the addition of glPixelStorei(GL_PACK_ALIGNMENT,1)
![alt text](Unresized.png)

# Resizing a bit-correct
![alt text](Resized_correct.png)

# Resizing more horizontally cuts the triangle horizontally
![alt text](Resized_horizontal_bug.png)
