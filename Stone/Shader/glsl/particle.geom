#version 460 core
layout(points) in;
layout(points, max_vertices = 30) out;

layout (location = 0) in float  in_Type[]; 
layout (location = 1) in vec3   in_Position[]; 
layout (location = 2) in vec3   in_Velocity[]; 
layout (location = 3) in float  in_Age[]; 

layout (location = 0) out float     out_Type; 
layout (location = 1) out vec3      out_Position; 
layout (location = 2) out vec3      out_Velocity; 
layout (location = 3) out float     out_Age; 

layout (binding = 0) uniform sampler1D randomTexture;

layout(std140, binding = 4) uniform RendererUniformBuffer
{
	float u_DeltaTime;
	float u_GlobalTime;
};

layout(std140, binding = 5) uniform ParticleUniformBuffer
{
	float u_LauncherLifetime;
	float u_ShellLifetime;
};  float u_SecondaryShellLifetime;

layout(std140, binding = 0) uniform CameraBlock
{
	mat4 u_ViewProjection;
	vec3 u_CameraPos;
};

vec3 GetRandomDir(float TexCoord)                                                   
{                                                                                   
     vec3 Dir = texture(randomTexture, TexCoord).xyz;
     Dir -= vec3(0.5, 0.5, 0.5);
     return Dir;                                                                    
}              

#define PARTICLE_TYPE_LAUNCHER 0.0f                                                 
#define PARTICLE_TYPE_SHELL 1.0f                                                    
#define PARTICLE_TYPE_SECONDARY_SHELL 2.0f     

void main()
{
    float current_Age = in_Age[0] + u_DeltaTime * 1000;                                         
                                                                                    
    if (in_Type[0] == PARTICLE_TYPE_LAUNCHER) {                                       
        if (current_Age >= u_LauncherLifetime) {                                             
            out_Type = PARTICLE_TYPE_SHELL;                                            
            out_Position = in_Position[0];                                               
            vec3 Dir = GetRandomDir(u_GlobalTime/1000.0);                                  
            Dir.y = max(Dir.y, 0.5);                                                
            out_Velocity = normalize(Dir) / 20.0;                                      
            out_Age = 0.0;
            gl_Position = u_ViewProjection * vec4(out_Position, 1.0);
            EmitVertex();                                                           
            EndPrimitive();                                                         
            current_Age = 0.0;                                                              
        }                                                                           
                                                                                    
        out_Type = PARTICLE_TYPE_LAUNCHER;                                             
        out_Position = in_Position[0];                                                   
        out_Velocity = in_Velocity[0];                                                   
        out_Age = current_Age;
        gl_Position = u_ViewProjection * vec4(out_Position, 1.0);
        EmitVertex();                                                               
        EndPrimitive();                                                             
    }                                                                               
    else {                                                                          
        float DeltaTimeSecs = u_DeltaTime * 1000 / 1000.0f;                           
        float t1 = in_Age[0] / 1000.0;                                                
        float t2 = current_Age / 1000.0;                                                    
        vec3 DeltaP = DeltaTimeSecs * in_Velocity[0];                                 
        vec3 DeltaV = vec3(DeltaTimeSecs) * (0.0, -9.81, 0.0);                      
                                                                                    
        if (in_Type[0] == PARTICLE_TYPE_SHELL)  {                                     
	        if (current_Age < u_ShellLifetime) {                                             
	            out_Type = PARTICLE_TYPE_SHELL;                                        
	            out_Position = in_Position[0] + DeltaP;                                  
	            out_Velocity = in_Velocity[0] + DeltaV;                                  
	            out_Age = current_Age;
                gl_Position = u_ViewProjection * vec4(out_Position, 1.0);
	            EmitVertex();                                                       
	            EndPrimitive();                                                     
	        }                                                                       
            else {                                                                  
                for (int i = 0 ; i < 10 ; i++) {                                    
                     out_Type = PARTICLE_TYPE_SECONDARY_SHELL;                         
                     out_Position = in_Position[0];                                      
                     vec3 Dir = GetRandomDir((u_GlobalTime + i)/1000.0);                   
                     out_Velocity = normalize(Dir) / 20.0;                             
                     out_Age = 0.0f; 
                     gl_Position = u_ViewProjection * vec4(out_Position, 1.0);
                     EmitVertex();                                                  
                     EndPrimitive();                                                
                }                                                                   
            }                                                                       
        }                                                                           
        else {                                                                      
            if (current_Age < u_SecondaryShellLifetime) {                                    
                out_Type = PARTICLE_TYPE_SECONDARY_SHELL;                              
                out_Position = in_Position[0] + DeltaP;                                  
                out_Velocity = in_Velocity[0] + DeltaV;                                  
                out_Age = current_Age; 
                gl_Position = u_ViewProjection * vec4(out_Position, 1.0);
                EmitVertex();                                                       
                EndPrimitive();                                                     
            }                                                                       
        }                                                                           
    }              
}