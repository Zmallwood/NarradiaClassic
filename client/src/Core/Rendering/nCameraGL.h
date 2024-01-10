#pragma once

namespace Narradia {
   class nCameraGL : public Singleton<nCameraGL> {
     public:
      auto PerspMatrix() {
         return m_perspMatrix;
      }
      void SetPerspMatrix(glm::mat4 _value) {
         m_perspMatrix = _value;
      }
      auto ViewMatrix() {
         return m_viewMatrix;
      }
      void SetViewMatrix(glm::mat4 _value) {
         m_viewMatrix = _value;
      }

     private:
      glm::mat4 m_perspMatrix;
      glm::mat4 m_viewMatrix;
   };
}
