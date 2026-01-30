#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>

class	Window {
	public:
		unsigned int	width;
		unsigned int	height;

	private:
		GLFWwindow*	_id = nullptr;
		bool				_isInit = false;

	public:
		Window(void);
		~Window();
		
		bool	shouldClose(void) const;
		bool	isKeyPressed(int key) const;
		bool	isKeyReleased(int key) const;

		int		init(unsigned int width, unsigned int	height, const char* title);
		void	destroy(void);
		void	close(void) const;
		void	update(void) const;

};

#endif /* WINDOW_HPP ======================================================== */
