xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template IndexedColor {
 <1630b820-7842-11cf-8f52-0040333594a3>
 DWORD index;
 ColorRGBA indexColor;
}

template MeshVertexColors {
 <1630b821-7842-11cf-8f52-0040333594a3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material Multimaterial_TRAIL_01Sub0 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "DM.tga";
 }
}

Frame thrust_01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  12;
  0.707107;-0.707107;0.000000;,
  0.000000;0.000000;0.000000;,
  0.000000;0.000000;-10.346713;,
  0.000000;0.000000;0.000000;,
  -0.707107;0.707107;-0.000000;,
  0.000000;0.000000;-10.346713;,
  0.707107;0.707107;0.000000;,
  -0.000000;0.000000;0.000000;,
  0.000000;0.000000;-10.346713;,
  -0.000000;0.000000;0.000000;,
  -0.707107;-0.707107;-0.000000;,
  0.000000;0.000000;-10.346713;;
  4;
  3;0,2,1;,
  3;3,5,4;,
  3;6,8,7;,
  3;9,11,10;;

  MeshNormals  {
   4;
   0.707107;0.707107;0.000000;,
   0.707107;0.707107;0.000000;,
   -0.707107;0.707107;0.000000;,
   -0.707107;0.707107;0.000000;;
   4;
   3;0,0,0;,
   3;1,1,1;,
   3;2,2,2;,
   3;3,3,3;;
  }

  MeshMaterialList  {
   1;
   4;
   0,
   0,
   0,
   0;
   { Multimaterial_TRAIL_01Sub0 }
  }

  MeshVertexColors  {
   12;
   0;1.000000;1.000000;1.000000;-1.000000;;,
   1;1.000000;1.000000;1.000000;-1.000000;;,
   2;1.000000;1.000000;1.000000;-1.000000;;,
   3;1.000000;1.000000;1.000000;-1.000000;;,
   4;1.000000;1.000000;1.000000;-1.000000;;,
   5;1.000000;1.000000;1.000000;-1.000000;;,
   6;1.000000;1.000000;1.000000;-1.000000;;,
   7;1.000000;1.000000;1.000000;-1.000000;;,
   8;1.000000;1.000000;1.000000;-1.000000;;,
   9;1.000000;1.000000;1.000000;-1.000000;;,
   10;1.000000;1.000000;1.000000;-1.000000;;,
   11;1.000000;1.000000;1.000000;-1.000000;;;
  }

  MeshTextureCoords  {
   12;
   0.998047;0.998047;,
   0.999512;0.844727;,
   -0.001513;0.998047;,
   0.999512;0.844727;,
   0.998047;0.998047;,
   -0.001513;0.998047;,
   0.998047;0.998047;,
   0.999512;0.844727;,
   -0.001513;0.998047;,
   0.999512;0.844727;,
   0.998047;0.998047;,
   -0.001513;0.998047;;
  }

  FVFData  {
   258;
   24;
   1065320448,
   1065320448,
   1065345024,
   1062748160,
   3133562880,
   1065320448,
   1065345024,
   1062748160,
   1065320448,
   1065320448,
   3133562880,
   1065320448,
   1065320448,
   1065320448,
   1065345024,
   1062748160,
   3133562880,
   1065320448,
   1065345024,
   1062748160,
   1065320448,
   1065320448,
   3133562880,
   1065320448;
  }
 }
}