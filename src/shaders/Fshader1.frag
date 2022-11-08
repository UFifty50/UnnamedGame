#version 460 core


in vec2 UV;

out vec4 colour;

uniform sampler2D textureSampler;

void main() {
  colour = texture(textureSampler , UV);
//    colour =
//        // Ambient
//        matAmbientColour +
//         Diffuse
//        matDiffuseColour * lightColour * lightIntensity * cosTheta / (distance*distance);
//        Specular
//        matSpecularColour * lightColour * lightIntensity * pow(cosAlpha, 5) / (distance*distance);
}
