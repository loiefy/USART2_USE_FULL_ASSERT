/*ring_buffer.h*/
#ifndef __ULTILS_H
#define __ULTILS_H

#define BUFFER_SIZE 64

typedef struct ring_buffer_typdef
{
	unsigned char buffer[BUFFER_SIZE];
	volatile unsigned int head;
	volatile unsigned int tail;
	//unsigned char buffer_size;
}ring_buffer_typdef;

//void ring_buffer_init(ring_buffer_typdef * buff, int size);
void ring_buffer_push(ring_buffer_typdef * buff, unsigned char data);
char ring_buffer_pop(ring_buffer_typdef * buff);

#endif
