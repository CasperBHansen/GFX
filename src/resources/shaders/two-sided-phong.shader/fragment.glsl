#version 110

uniform vec3 eye;

uniform vec3 Ai;

uniform vec3 Lp;
uniform vec3 Li;

uniform vec3 Oa;
uniform vec3 Od;
uniform vec3 Os;

uniform float Ka;
uniform float Kd;
uniform float Ks;

uniform float n;
uniform float Fatt;

varying vec3 N;
varying vec3 P;

void main() {
    
    vec3 E = normalize(eye - P); // eye vector
    vec3 L = normalize(Lp - P);  // light vector
    
    if ( gl_FrontFacing )
    {
        float NL = max(0.0, dot(N, L));
        float vAngle = dot(N, E);

        vec3 R = normalize((2.0 * N * NL) - L);
        if ( dot(R, N) < 0.0) R = vec3(0.0);

        float s = max(pow(dot(R, E), n), 0.0);

        vec3 R_a = Ai * Oa * Ka;
        vec3 R_d = Li * Od * Kd * NL;
        vec3 R_s = Li * Os * Ks * s;

        vec3 color = R_a + R_d + R_s;

        gl_FragColor = vec4(color.x, color.y, color.z, 1.0);
    }
    else
    {
        float NL = max(0.0, dot(-N, L));
        float vAngle = dot(-N, E);

        vec3 R = normalize((2.0 * (-N) * NL) - L);
        if ( dot(R, -N) < 0.0) R = vec3(0.0);

        float s = max(pow(dot(R, E), n), 0.0);

        vec3 R_a = Ai * Oa * Ka;
        vec3 R_d = Li * Od * Kd * NL;
        vec3 R_s = Li * Os * Ks * s;

        vec3 color = R_a + R_d + R_s;

        gl_FragColor = vec4(0.81 - color.y, 0.81 - color.x, 0.81 - color.z, 1.0);
    }
}

