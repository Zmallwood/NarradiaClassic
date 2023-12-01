#include "DoCompileShader.h"

namespace Narradia {

    /**
     * Compile shader.
     */
    GLuint DoCompileShader(
        const GLchar *shader_src, GLuint *shader, GLenum shader_type) {
        *shader = glCreateShader(shader_type);
        glShaderSource(*shader, 1, &shader_src, NULL);
        glCompileShader(*shader);
        GLint shader_compiled = GL_FALSE;
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_compiled);

        return shader_compiled;
    }
}
