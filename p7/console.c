#include <string.h>
#include <ctype.h>
#include "uart1.h"
#include "adc.h"


// Definiciones para el manejo de los comandos de consola
#define MAX_CMD_PARAMS 16
typedef int cmdclbk(int argc, char *argv[]);
static int parse_cmd(char* cmd, char** argv);
static cmdclbk* get_cmd(char *cmd);
static char prompt[] = "LabEC> ";

int console(void)
{
	unsigned int ncar = 0,c;
	char line[256];
	char* argv[MAX_CMD_PARAMS];
	int argn;
	cmdclbk* cmd;

	// Bucle infinito
    while(1)
    {
    	uart1_printf(prompt);
        uart1_readline(line, 256);
        argn = parse_cmd(line, argv);
        if (argn > 0) {
        	cmd = get_cmd(argv[0]);
        	if (cmd)
        		cmd(argn, argv);
        	else
        		uart1_printf("error: command not found!\n");
        }
    }
}

int adcread(int argc, char *argv[])
{
	//uart1_printf("Should read from adc\n");
	int val;
	int chan = 0;
	val = adc_read(chan);
	uart1_printf("ADC chan %d: %d (0x%X)\t%d mV\n", chan, val, val, (val*3300)/1024);
	return 0;
}

int help(int argc, char *argv[]);

/* Tabla de comandos */
struct cmd_reg {
	char *name;
	char *helpmsg;
	cmdclbk *cmd;
};

struct cmd_reg cmds[] = {
		"adcread", "reads from the ADC", adcread,
		"help", "shows help messages for all commands", help,
		NULL,NULL,NULL
};

int help(int argc, char *argv[])
{
	struct cmd_reg *p = cmds;
	while (p->name) {
		uart1_printf("%-10s\t%-20ls\n",p->name, p->helpmsg);
		p++;
	}
	return 0;
}

static char * next_noblank(char *str)
{
	while (*str && isspace(*str))
		str++;
	return str;
}

static char * next_blank(char *str)
{
	while (*str && !isspace(*str))
		str++;
	return str;
}

static int parse_cmd(char *cmd, char *argv[MAX_CMD_PARAMS])
{
	int i;

	cmd = next_noblank(cmd);
	if (!*cmd)
		return 0;
	argv[0] = cmd;
	i = 1;
	while (i < MAX_CMD_PARAMS) {
		cmd = next_blank(cmd);
		if (!*cmd)
			return i;
		*cmd = '\0';
		cmd++;
		cmd = next_noblank(cmd);
		if (!*cmd)
			return i;
		argv[i] = cmd;
		i++;
	}
	return i;
}

static cmdclbk* get_cmd(char *cmd)
{
	struct cmd_reg *p = cmds;
	cmdclbk *clbk = NULL;
	while (p->name && strncmp(cmd,p->name,strlen(cmd)))
		p++;
	if (p->name != NULL)
		clbk = p->cmd;
	return clbk;
}
