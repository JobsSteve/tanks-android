uniform mat4 mModelView;
uniform mat4 mModelViewProjection;
uniform mat4 mNormalMatrix;

attribute vec3 vPosition;
attribute vec3 vNormal;

varying vec3 N;
varying vec3 v;

void main()
{
    v = vec3(mModelView * vec4(vPosition, 1.0));
    N = (mNormalMatrix * vec4(vNormal, 1.0)).xyz;

    gl_Position = mModelViewProjection * vec4(vPosition, 1.0);
}
