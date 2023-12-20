
#include "protocol.h"


/* define */
static const c8 ProtEntete[] = "##N,B,A:";
static const c8 ProtEntete_T[] = "##N,B,T:";
//static const c8 noFailed[] = "OK";
static const c8 Failed[] = "FAILED";
static const c8 noFailed[] = "OK";
static const c8 InvalideMessage[] = "Msg error";


#define COM_ARG_PREFIX                 '='
#define COM_ANS_PREFIX                 '['
#define COM_ANS_SUFFIX                 ']'
#define COM_DATA_PREFIX                ':'
#define COM_DATA_ZERO                  '0' 
#define COM_DATA_SPACE                 ' ' 

#define READ_COMMAND                   false
#define WRITE_COMMAND                  true
 const c8 CrLf[] = "\r\n";

 
static		u8 Com_HdlGetId( c8* p_c8_tabRecept,u8 *point,u8 u8_Write);
static		u8 GetAngle1( c8* p_c8_tabRecept,u8 *point,u8 u8_Write);  
static		u8 GetAngle2( c8* p_c8_tabRecept,u8 *point,u8 u8_Write); 
static		u8 GetMagxyz( c8* p_c8_tabRecept,u8 *point,u8 u8_Write);  
static		u8 SetFloat( c8* p_c8_tabRecept,u8 *point,u8 u8_Write); 
static		u8 GetFloat( c8* p_c8_tabRecept,u8 *point,u8 u8_Write); 
static		u8 GetNbTours( c8* p_c8_tabRecept,u8 *point,u8 u8_Write);
static		u8 GetPosition( c8* p_c8_tabRecept,u8 *point,u8 u8_Write); 
static		u8 GetBat( c8* p_c8_tabRecept,u8 *point,u8 u8_Write) ;  


void read_angle1(float *angle);
void read_angle2(float *angle);
void read_mag_xyz(float *mag_x,float *mag_y,float *mag_z);
float read_adc(void);


void u32_stackEnvoi(u8 *point);
typedef enum 
{ 
  NO_DEFAULT,
	DEFAULT_FORMAT,
	DEFAULT_PARAMATERS
} PROTOCOL_ERRORS;



typedef struct {
c8 *command;                 /* command string */
c8 **response;               /* Response string */	
void *parameter;             /* Response string */	  
u32 size;  
u8 readWrite;                   
u8 (*fct)(c8*,u8*,u8);          /* Fonction de traitement de la commande*/

} struct_tab_Com_CmdList;

static c8 c8_response[100];
static c8 *p_c8_response = c8_response;


void algoVolume(VOLUME *v);
void algoPosition(POSITION *d);



/* structure command protocol unified */

static const struct_tab_Com_CmdList Com_CmdList[] =
{
  
    /*  name                  / buffer reponse / param�tre � modifier /                                 / format/     /read/write/             fonction */
    { "Count.getId"           ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,Com_HdlGetId },   
    {"Angle.getAngle1"        ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,GetAngle1 },   
    {"Angle.getAngle2"        ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,GetAngle2 },   
    {"Mag.getxyz"             ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,GetMagxyz },  
    {"Algo.getK_common"       ,&p_c8_response,&param_flash.s_element.Param_mesure_volume.K_common         , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getAngle_2_offset" ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.angle_2_offset  , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getx_0_init"       ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.x_0_init        , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getx_0_offset"      ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.x_0_offset      , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getKa_BxC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Ka_BxC3       , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getKb_BxC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Kb_BxC3       , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getKa_ByC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Ka_ByC3       , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getKb_ByC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Kb_ByC3       , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getKa_BzC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Ka_BzC3       , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.getKb_BzC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Kb_BzC3       , (u32) NULL ,READ_COMMAND           ,GetFloat },  
    {"Algo.setK_common"       ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.K_common        , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setAngle_2_offset" ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.angle_2_offset  , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setx_0_init"       ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.x_0_init        , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setx_0_offset"      ,&p_c8_response ,&param_flash.s_element.Param_mesure_volume.x_0_offset      , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setKa_BxC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Ka_BxC3       , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setKb_BxC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Kb_BxC3       , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setKa_ByC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Ka_ByC3       , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
   {"Algo.setKb_ByC3"         ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Kb_ByC3       , (u32) NULL ,WRITE_COMMAND          ,SetFloat }, 
    {"Algo.setKa_BzC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Ka_BzC3       , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    {"Algo.setKb_BzC3"        ,&p_c8_response ,&param_flash.s_element.Param_mesure_position.Kb_BzC3       , (u32) NULL ,WRITE_COMMAND          ,SetFloat },  
    { "Algo.getNb_tour"       ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,GetNbTours },   
    { "Algo.getPosition"      ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,GetPosition },   
    { "Main.getbat"           ,&p_c8_response ,NULL                                                       , (u32) NULL ,READ_COMMAND           ,GetBat },   
  
  };



/*!========================================================================================
 
\brief Name         :  v_unifiedProtocol
                                                                          
\brief Function description       :  function  unified protocol
                                                                                                
 

\param[in]        p_u8_tabRecept : recept buffer        
   


\param[out]       none     
                                                                                                                                  
==============================================================
  CORRECTION / MODIFICATIONS : date : author : description                     
                                                                          
 \brief 11/03/21 FM: Creation                                                   
                                                                          
==============================================================*/  

void v_unifiedProtocol(u8* p_c8_tabRecept)
{
  u16 u16_count=0;
  c8* point = (c8*)p_c8_tabRecept;
  c8* point1=NULL;
  u8 cde_ok=FALSE;
  u32 l,l2,l3;
  c8 buffer[50];
  point = strchr(point,':' );
  point1 = strchr(point,'\r' );
  *point1 = 0;
  point1 = strchr(point,'\n' );
  *point1 = 0;
  c8 *p = NULL;
  u8 u8_Write = false;
  PROTOCOL_ERRORS u8_defaut_prot = NO_DEFAULT;
  NRF_LOG_DEBUG("Receive protocol");
  //NRF_LOG_HEXDUMP_DEBUG(p_c8_tabRecept, strlen((c8*)p_c8_tabRecept));
 //NRF_LOG_INFO("RX: %s",p_c8_tabRecept);
  if(point != NULL)
  {
    point++;
    strcpy(buffer,point);
    u8_defaut_prot = DEFAULT_FORMAT;
    NRF_LOG_DEBUG(buffer);
    if(p_c8_tabRecept[6] == 'C')
    {
      
      for (u16_count=0; u16_count < ( sizeof(Com_CmdList)/sizeof(struct_tab_Com_CmdList)); u16_count++)
      {
        l = (u8)strlen((const char*)Com_CmdList[u16_count].command);
        p = strchr(point,COM_ARG_PREFIX );
        
        if(p != 0)
        {
        l2 = p-point;
        l3 = strlen(p);
        u8_Write = true;  

        }
        else
        {
          p = strchr(point,(int)NULL );
          if(p != 0)
          {
           l2 = p-point;

          }
          else
          {
           
               p = NULL;
          }
           
        }

        if( (strncmp((const char*)Com_CmdList[u16_count].command, (const char*)point, l ) == 0) && (l == l2)    )
        {
          if(u8_Write == Com_CmdList[u16_count].readWrite)
          {
            if((l3 == 1) && (u8_Write == true))    /* test si carractere apr�s "="*/
            {
               u8_defaut_prot = DEFAULT_PARAMATERS;
            }
            else
            {
              cde_ok = Com_CmdList[u16_count].fct(point+l,(void*)&Com_CmdList[u16_count],u8_Write);
              u8_defaut_prot = NO_DEFAULT;
            }
          }
          else
          {
            u8_defaut_prot = DEFAULT_PARAMATERS;
          }
            
          
          break;   
        }
        else
        {
          u8_defaut_prot = DEFAULT_FORMAT;
        }
      }
    }
      else
      {
        cde_ok = false;    
        u8_defaut_prot = DEFAULT_FORMAT;
      }
    if(cde_ok== true)
    {
      if(**Com_CmdList[u16_count].response != (int)NULL)  
      {
        point = *Com_CmdList[u16_count].response;
        point[4] = 'B';
       

        
        
        u32_stackEnvoi((u8*)*Com_CmdList[u16_count].response );
      }
    }	
    else
    {

     if(u8_defaut_prot == DEFAULT_PARAMATERS)
      {
       sprintf(p_c8_response,"%s%s[%s]%s",ProtEntete,(c8*)Com_CmdList[u16_count].command,Failed,CrLf);

       u32_stackEnvoi((u8*)p_c8_response);
        
      }
      else //(u8_defaut_prot == DEFAULT_FORMAT)
      {
        sprintf(p_c8_response,"%s%s%s",ProtEntete_T,InvalideMessage,CrLf);
        point[4] = 'H';

        u32_stackEnvoi((u8*)p_c8_response);
      }
    }
   
  }
  else
  {
        sprintf(p_c8_response,"%s%s%s",ProtEntete_T,InvalideMessage,CrLf);
        point[4] = 'H';

        u32_stackEnvoi((u8*)p_c8_response);
  }

}  

static		u8 Com_HdlGetId( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
 
    struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
    sprintf(*parameters->response,"%s%s[%s-%s]%s",ProtEntete,parameters->command,"Counter","V1.00.00",CrLf);
   NRF_LOG_INFO("Command :%s",parameters->command);


 return(true);
}

static		u8 GetAngle1( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
   float angle;
   read_angle1(&angle);
   sprintf(*parameters->response,"%s%s[%.3f]%s",ProtEntete,parameters->command,angle,CrLf);
   return(true);
}

static		u8 GetAngle2( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
   float angle;
   read_angle2(&angle);
   sprintf(*parameters->response,"%s%s[%.3f]%s",ProtEntete,parameters->command,angle,CrLf);
   return(true);
}

static		u8 GetMagxyz( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
   float mag_x = 0;
   float mag_y = 0;
   float mag_z = 0;
   read_mag_xyz(&mag_x,& mag_y,& mag_z); 
   sprintf(*parameters->response,"%s%s[%.3f,%.3f,%.3f]%s",ProtEntete,parameters->command,mag_x,mag_y,mag_z,CrLf);
   return(true);
}


static		u8 SetFloat( c8* p_c8_tabRecept,u8 *point_in,u8 u8_Write)  
{
struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point_in;
 c8* point = NULL;  
 float f_value = 0;

 point = p_c8_tabRecept;
 point = strchr(point,COM_ARG_PREFIX );
 point++;
 
if(strlen(point) <= 10)
{
    
   f_value = atof(point);
  *(float*)parameters->parameter = f_value;
  ind_flash=true;
    Write_data_to_flash((u32*)&param_flash,0xF0000);

   sprintf(*parameters->response,"%s%s[%s]%s",ProtEntete,parameters->command,noFailed,CrLf);

}
else
{
  sprintf(*parameters->response,"%s%s[%s]%s",ProtEntete,parameters->command,Failed,CrLf); 
}
return(true);
}



static		u8 GetFloat( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{

   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
  sprintf(*parameters->response,"%s%s[%.3f]%s",ProtEntete,parameters->command, *(float*)parameters->parameter,CrLf);
   return(true);
}

static		u8 GetBat( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
   float value;
value= read_adc();

  sprintf(*parameters->response,"%s%s[%.3f]%s",ProtEntete,parameters->command, value,CrLf);
   return(true);
}





static		u8 GetNbTours( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
 

  algoVolume(&s_volume);
  sprintf(*parameters->response,"%s%s[%.3f]%s",ProtEntete,parameters->command, s_volume.result.number_of_turns,CrLf);
   return(true);
}


static		u8 GetPosition( c8* p_c8_tabRecept,u8 *point,u8 u8_Write)  
{
   struct_tab_Com_CmdList *parameters = (struct_tab_Com_CmdList*) point;
 
   algoPosition(&s_position);
  sprintf(*parameters->response,"%s%s[%.3f]%s",ProtEntete,parameters->command, s_position.result.position,CrLf);
   return(true);
}

void read_angle1(float *angle)
{
   MA780_open_SPI_1();
   *angle = f_readAngle(CS_ANGLE1);
   MA780_close_SPI_1();
}
void read_angle2(float *angle)
{
   MA780_open_SPI_1();
   *angle = f_readAngle(CS_ANGLE2);
   MA780_close_SPI_1();
}

void read_mag_xyz(float *mag_x,float *mag_y,float *mag_z) 
{
   MLX90393_open_SPI();
   MLX90393_readData(mag_x,mag_y,mag_z) ;
   MLX90393_close_SPI();
}
  

