precision mediump float;

uniform vec4 vColor;
uniform vec3 vLightSource0;

varying vec3 N;
varying vec3 v;

void main()
{
    vec3 nhat = normalize(N);
    vec3 L = normalize(vLightSource0 - v);
    vec3 E = normalize(-v);
    vec3 R = normalize(-reflect(L, nhat));

    vec4 Iamb = vColor * 0.2;
    Iamb = clamp(Iamb, 0.0, 1.0);

    vec4 Idiff = vColor * vec4(0.5, 0.5, 0.5, 1.0) * max(dot(nhat, L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);

    vec4 Ispec = vColor * vec4(1.0, 1.0, 1.0, 1.0) * pow(max(dot(R, E), 0.0), 30.0);
    Ispec = clamp(Ispec, 0.0, 1.0);

    vec4 tmp = Iamb + Idiff + Ispec;
    tmp.w = 1.0;
    gl_FragColor = clamp(tmp, 0.0, 1.0);
}
