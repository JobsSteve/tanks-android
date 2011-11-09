uniform mat4 mModelView;

attribute vec4 vPosition;
attribute vec4 vNormal;

varying vec4 N;

void main()
{
    gl_Position = mModelView * vPosition;
    N = vNormal;
}
