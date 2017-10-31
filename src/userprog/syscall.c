#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "string.h"
#include "pagedir.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //printf ("System Call!\n");
  //thread_exit ();
  int *argv;
  argv=(int*)f->esp;
 /*if(!valid_ptr(f->esp))
  {
	  fail_exit(f->eax);
  }*/
  switch(argv[0])
  {
	  case SYS_HALT:
		shutdown_power_off();
	  break;      
	             
      case SYS_EXIT:
		f->eax=argv[1];
		//f->esp+=sizeof(int);
		thread_exit();
      break;   
                    
      case SYS_EXEC:
      break;                  
      case SYS_WAIT:
      break;                 
      case SYS_CREATE:
      break;                
      case SYS_REMOVE:
      break;  
                     
      case SYS_OPEN:
		if(!valid_ptr(argv[1]))
		{
			fail_exit(f->eax);		  
		}
	   /*critical section*/
		struct file *newf=filesys_open((char*)argv[1]);
		if(newf=NULL)
		{
		   *(int*)f->eax=-1;
		}
		struct thread *t=thread_current();
		struct pfile *newp=malloc(sizeof(struct pfile));
		t->fd++;
		newp->fd=t->fd;
		newp->filename=newf;
		list_push_back(&t->file_list,&newp->elem);
		f->eax=t->fd;
      break;
                         
      case SYS_FILESIZE:
      break;              
      case SYS_READ: 
		thread_exit();
      break;  
                     
      case SYS_WRITE:
		if(argv[5]==1)
		{
		   /*if(!valid_ptr((void*)argv[6]))
		   {
			  fail_exit(f->eax);
		   }*/
		   putbuf(argv[6],argv[7]);
		}
		f->eax=argv[7];
      break;     
                   
      case SYS_SEEK:
      break;                   
      case SYS_TELL:
      break;                   
      case SYS_CLOSE:
      break;
      default:
		thread_exit();      
	  }
}

int
valid_ptr(void *addr)
{
	int *a=(int*)pagedir_get_page(thread_current()->pagedir,addr);
	if(a==NULL)
	{
		return 0;
	}
	return 1;
}

void
fail_exit(void *f)
{
	f=-1;
	thread_exit();
}	
