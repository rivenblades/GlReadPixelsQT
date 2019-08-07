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

# Image is with green background now
![alt text](QImage_fill_green.png)

# Calling glfwSetWindowSize(window,m_width,m_height); in resizeEvent of Qt fixed it
![alt text](Correct_Needed_glfwSetWindowSize_when_resizing_qt_window.png)
