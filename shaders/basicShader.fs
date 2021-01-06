#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;
uniform vec4 Test;
void main()
{
	gl_FragColor = (texture2D(sampler, texCoord0) + Test) * 
		clamp(dot(-lightDirection, normal0), 0.2, 1.0);
}
