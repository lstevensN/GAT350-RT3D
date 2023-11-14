#version 430

#define INVERT_MASK      (1 << 0)
#define GRAYSCALE_MASK   (1 << 1)
#define COLOR_TINT_MASK  (1 << 2)
#define GRAIN_MASK       (1 << 3)
#define SCANLINE_MASK    (1 << 4)
#define CUSTOM_MASK      (1 << 5)

in layout(location = 0) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;
uniform vec3 tint;
uniform float time;

layout(binding = 0) uniform sampler2D screenTexture;


float random(in vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 invert(in vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 grayscale(in vec4 color)
{
	return vec4(vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b), color.a);
}

vec4 ctint(in vec4 color)
{
	return vec4(color.rgb + tint, color.a);
}

vec4 grain(in vec4 color)
{
	return color * random(gl_FragCoord.xy + time);
}

vec4 scanline(in vec4 color)
{
	int scanline = int(gl_FragCoord.y);
	return (scanline % 4 != 0) ? vec4(0, 0, 0, color.a) : color;
}

vec4 custom(in vec4 color)
{
	float kernel[9] = float[]
	(
		-1, -1, -1,
		-1,  5, -1,
		-1, -1, -1
	);

	// taken from https://www.turais.de/using-shaders-image-post-processing-with-convolution/ (thank you for the link)
	ivec2 texture_size = textureSize(screenTexture, 0);
    vec2 step_size = 1.0/texture_size;

    vec2 offsets[9] = vec2[](
        vec2(-step_size.x,  -step_size.y),
        vec2( 0.0f,         -step_size.y),
        vec2( step_size.x,  -step_size.y),
        vec2(-step_size.x,   0.0f),
        vec2( 0.0f,          0.0f),
        vec2( step_size.x,   0.0f),
        vec2(-step_size.x,  +step_size.y),
        vec2( 0.0f,         +step_size.y),
        vec2( step_size.x,   step_size.y)
    );

	vec4 sum = vec4(0.0);
    for(int i = 0; i < 9; i++) {
        sum += texture(screenTexture, ftexcoord + offsets[i]) * kernel[i];
    }

	sum.a = color.a;
	return sum;
}



void main()
{
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;

	if (bool(params & INVERT_MASK))      postprocess = invert(postprocess);
	if (bool(params & GRAYSCALE_MASK))   postprocess = grayscale(postprocess);
	if (bool(params & COLOR_TINT_MASK))  postprocess = ctint(postprocess);
	if (bool(params & GRAIN_MASK))       postprocess = grain(postprocess);
	if (bool(params & SCANLINE_MASK))    postprocess = scanline(postprocess);
	if (bool(params & CUSTOM_MASK))	     postprocess = custom(postprocess);

	ocolor = mix(basecolor, postprocess, blend);
}
