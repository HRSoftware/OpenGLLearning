#include "Renderer.h"
#include <string>
#include "../Shader.h"


void Renderer::setCamera(Camera& cam)
{
    _currentCamera = &cam;
}

void Renderer::renderGameObject(GameObject* gameobj, Shader shader)
{
        
    for ( auto m : gameobj->getMeshes() )
    {
        setUpShader(m.textureHandles, shader, true);
        shader.setMat4("view", _currentCamera->GetViewMatrix());
        shader.setMat4("model", gameobj->getModelMatrix());
        renderMesh(m.VAO, m.indices.size(), 0);
    }
}

void Renderer::renderMesh(int VAO, int indiceCount, int framebuffer)
{
    glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::setUpShader(map<int, string> textures, Shader shader, bool textured)
{
    if (textured) {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        int _textureIndex = 0;
        for ( auto _texture : textures )
        {
            glActiveTexture(GL_TEXTURE0 + _textureIndex);
            std::string number;
            std::string name = _texture.second;


            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            shader.setInt((name + number).c_str(), _textureIndex);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, _texture.first);

            _textureIndex++;
        }


        //for (unsigned int i = 0; i < textures.size(); i++) {
        //    glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //                                      // retrieve texture number (the N in diffuse_textureN)
        //    std::string number;
        //    std::string name = textures[i]->type;

        //    if (name == "texture_diffuse")
        //        number = std::to_string(diffuseNr++);
        //    else if (name == "texture_specular")
        //        number = std::to_string(specularNr++); // transfer unsigned int to stream
        //    else if (name == "texture_normal")
        //        number = std::to_string(normalNr++); // transfer unsigned int to stream
        //    else if (name == "texture_height")
        //        number = std::to_string(heightNr++); // transfer unsigned int to stream

        //                                             // now set the sampler to the correct texture unit

        //    shader.setInt((name + number).c_str(), i);
        //    // and finally bind the texture
        //    glBindTexture(GL_TEXTURE_2D, textures[i]->ID);
        //}
    }
}

void Renderer::renderBatch(std::map<string, GameObject*>& renderBatch, Shader shader)
{
    for ( auto GO : renderBatch )
    {
        if(GO.second->isModelNULL() == false)
            renderGameObject(GO.second, shader);
    }
}
