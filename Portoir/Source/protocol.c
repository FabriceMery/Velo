
#include "protocol.h"


/* define */
static const c8 ProtEntete[] = "##N,B,A:";
static const c8 ProtEntete_T[] = "##N,B,T:";
static const c8 noFailed[] = "OK";
static const c8 Failed[] = "FAILED";
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

static c8 c8_response[50];
static c8 *p_c8_response = c8_response;





/* structure command protocol unified */

static const struct_tab_Com_CmdList Com_CmdList[] =
{
  
    /*  name             / buffer reponse / paramètre à modifier /                       / format/                 / fonction */
    { "Pip.getId"       ,&p_c8_response ,NULL                                           ,NULL                     ,READ_COMMAND           ,Com_HdlGetId },   
  
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
  NRF_LOG_HEXDUMP_DEBUG(p_c8_tabRecept, strlen(p_c8_tabRecept));
 //NRF_LOG_INFO("RX: %s",p_c8_tabRecept);
  if(point != NULL)
  {
    point++;
    strcpy(buffer,point);
    u8_defaut_prot = DEFAULT_FORMAT;
    
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
          p = strchr(point,NULL );
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
            if((l3 == 1) && (u8_Write == true))    /* test si carractere après "="*/
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
      if(**Com_CmdList[u16_count].response != NULL)  
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
    sprintf(*parameters->response,"%s%s[%s-%s]%s",ProtEntete,parameters->command,"P 200","V1.00.00",CrLf);
   NRF_LOG_INFO("Command :%s",parameters->command);


 return(true);
}




