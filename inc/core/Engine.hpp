#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <imgui/imgui.h>
# include <imgui/imgui_impl_glfw.h>
# include <imgui/imgui_impl_opengl3.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

# include <exception>

# include <core/Window.hpp>
# include <core/Object.hpp>
# include <core/Shader.hpp>
# include <core/Camera.hpp>

class	Engine {
	public:
		Window	window;
		Camera	camera;

	private:
		float	_lastFrame;
		float	_deltaTime;


	public:
		Engine(void);
		~Engine();

		void	run(void);
	
	private:
		void	_initGLFW(void) const;
		void	_initGLAD(void) const;
		void	_handleInput(void) const;
		void	_updateDeltaTime(void);


	public:
		class	WindowInitFailedException: std::exception {
			virtual const char*	what(void) const noexcept;	
		};

		class	GladLoadFailedException: std::exception {
			virtual const char*	what(void) const noexcept;	
		};
};

#endif /* ENGINE_HPP ======================================================== */
