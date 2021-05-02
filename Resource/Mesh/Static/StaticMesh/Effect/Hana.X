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


Material Multimaterial_hanabira_01Sub0 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "DM.tga";
 }
}

Frame hanabira {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  12;
  0.000000;0.879365;-4.000000;,
  -3.000000;0.952550;-1.333333;,
  -3.000000;1.831915;-4.000000;,
  0.000000;0.000000;-1.333333;,
  3.000000;1.831915;-4.000000;,
  -3.000000;0.952550;1.333333;,
  3.000000;0.952550;-1.333333;,
  0.000000;-0.000000;1.333333;,
  -3.000000;1.831915;4.000000;,
  0.000000;0.879365;4.000000;,
  3.000000;0.952550;1.333333;,
  3.000000;1.831915;4.000000;;
  12;
  3;0,2,1;,
  3;1,3,0;,
  3;3,4,0;,
  3;1,5,3;,
  3;3,6,4;,
  3;3,7,6;,
  3;3,5,7;,
  3;7,5,8;,
  3;8,9,7;,
  3;9,10,7;,
  3;7,10,6;,
  3;9,11,10;;

  MeshNormals  {
   15;
   0.000000;0.949696;0.313173;,
   0.288704;0.909256;0.299838;,
   0.288704;0.909256;0.299838;,
   0.288704;0.909256;0.299838;,
   0.000000;0.988069;0.154009;,
   -0.288704;0.909256;0.299838;,
   0.302628;0.953109;0.000000;,
   0.302628;0.953109;0.000000;,
   -0.298917;0.941422;0.156120;,
   -0.000000;0.988069;-0.154009;,
   0.288704;0.909256;-0.299838;,
   0.288704;0.909256;-0.299838;,
   0.000000;0.949696;-0.313174;,
   -0.298917;0.941422;-0.156120;,
   -0.288704;0.909256;-0.299838;;
   12;
   3;0,1,2;,
   3;3,4,0;,
   3;4,5,0;,
   3;6,7,4;,
   3;4,8,5;,
   3;4,9,8;,
   3;4,7,9;,
   3;9,10,11;,
   3;11,12,9;,
   3;12,13,9;,
   3;9,13,8;,
   3;12,14,13;;
  }

  MeshMaterialList  {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { Multimaterial_hanabira_01Sub0 }
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
   0.500000;1.000000;,
   0.000031;0.666504;,
   0.000031;1.000000;,
   0.500000;0.666504;,
   1.000000;1.000000;,
   0.000031;0.333252;,
   1.000000;0.666504;,
   0.500000;0.333252;,
   0.000031;0.000031;,
   0.500000;0.000031;,
   1.000000;0.333252;,
   1.000000;0.000031;;
  }

  FVFData  {
   258;
   24;
   1056964608,
   1065353216,
   939524096,
   1059758080,
   939524096,
   1065353216,
   1056964608,
   1059758080,
   1065353216,
   1065353216,
   939524096,
   1051369472,
   1065353216,
   1059758080,
   1056964608,
   1051369472,
   939524096,
   939524096,
   1056964608,
   939524096,
   1065353216,
   1051369472,
   1065353216,
   939524096;
  }
 }
}