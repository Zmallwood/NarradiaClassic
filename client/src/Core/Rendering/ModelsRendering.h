#pragma once

namespace Narradia {
   void NewModel(StringView _modelName);
   // clang-format off
   void DrawModel(
       StringView _modelName, 
       float _msTime, 
       Point3F _position, 
       float _rotation = 0.0f,
       float _scaling = 1.0f, 
       float _brightness = 1.0f, 
       glm::vec3 _colorMod = {1.0f, 1.0f, 1.0f},
       bool _noFog = false, 
       bool _noLighting = false);
   // clang-format on
   void StartModelsBatchDrawing();
   void StopModelsBatchDrawing();
}
