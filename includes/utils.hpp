//
// Created by Giulio Fratini on 2/17/22.
//

#ifndef SCOP_CPP_UTILS_HPP
#define SCOP_CPP_UTILS_HPP

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		abort();
	}
}
#define AAA
#ifdef AAA
#define GL_CHECK(stmt) do { \
            while (glGetError() != GL_NO_ERROR); \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif


#endif //SCOP_CPP_UTILS_HPP
