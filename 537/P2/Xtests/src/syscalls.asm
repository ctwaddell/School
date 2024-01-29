
_syscalls:     file format elf32-i386


Disassembly of section .text:

00000000 <main>:
#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char* argv[])
{
   0:	f3 0f 1e fb          	endbr32 
   4:	8d 4c 24 04          	lea    0x4(%esp),%ecx
   8:	83 e4 f0             	and    $0xfffffff0,%esp
   b:	ff 71 fc             	pushl  -0x4(%ecx)
   e:	55                   	push   %ebp
   f:	89 e5                	mov    %esp,%ebp
  11:	53                   	push   %ebx
  12:	51                   	push   %ecx
  13:	83 ec 20             	sub    $0x20,%esp
  16:	89 cb                	mov    %ecx,%ebx
  int total = atoi(argv[1]);
  18:	8b 43 04             	mov    0x4(%ebx),%eax
  1b:	83 c0 04             	add    $0x4,%eax
  1e:	8b 00                	mov    (%eax),%eax
  20:	83 ec 0c             	sub    $0xc,%esp
  23:	50                   	push   %eax
  24:	e8 a8 02 00 00       	call   2d1 <atoi>
  29:	83 c4 10             	add    $0x10,%esp
  2c:	89 45 ec             	mov    %eax,-0x14(%ebp)
  int success = atoi(argv[2]);
  2f:	8b 43 04             	mov    0x4(%ebx),%eax
  32:	83 c0 08             	add    $0x8,%eax
  35:	8b 00                	mov    (%eax),%eax
  37:	83 ec 0c             	sub    $0xc,%esp
  3a:	50                   	push   %eax
  3b:	e8 91 02 00 00       	call   2d1 <atoi>
  40:	83 c4 10             	add    $0x10,%esp
  43:	89 45 e8             	mov    %eax,-0x18(%ebp)
  int swag = getpid();
  46:	e8 a0 03 00 00       	call   3eb <getpid>
  4b:	89 45 e4             	mov    %eax,-0x1c(%ebp)
  int calls = 0;
  4e:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%ebp)
  int goodcalls = 0;
  55:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%ebp)
  int bad = total - success;
  5c:	8b 45 ec             	mov    -0x14(%ebp),%eax
  5f:	2b 45 e8             	sub    -0x18(%ebp),%eax
  62:	89 45 d8             	mov    %eax,-0x28(%ebp)
  
  for(int i = 0; i < success; i++)
  65:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  6c:	eb 09                	jmp    77 <main+0x77>
  {
    getpid();
  6e:	e8 78 03 00 00       	call   3eb <getpid>
  for(int i = 0; i < success; i++)
  73:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  77:	8b 45 f4             	mov    -0xc(%ebp),%eax
  7a:	3b 45 e8             	cmp    -0x18(%ebp),%eax
  7d:	7c ef                	jl     6e <main+0x6e>
  }

  for(int j = 0; j < bad; j++)
  7f:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  86:	eb 11                	jmp    99 <main+0x99>
  {
    kill(-1);
  88:	83 ec 0c             	sub    $0xc,%esp
  8b:	6a ff                	push   $0xffffffff
  8d:	e8 09 03 00 00       	call   39b <kill>
  92:	83 c4 10             	add    $0x10,%esp
  for(int j = 0; j < bad; j++)
  95:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
  99:	8b 45 f0             	mov    -0x10(%ebp),%eax
  9c:	3b 45 d8             	cmp    -0x28(%ebp),%eax
  9f:	7c e7                	jl     88 <main+0x88>
  }

  
  
  calls = getnumsyscalls(swag);
  a1:	83 ec 0c             	sub    $0xc,%esp
  a4:	ff 75 e4             	pushl  -0x1c(%ebp)
  a7:	e8 5f 03 00 00       	call   40b <getnumsyscalls>
  ac:	83 c4 10             	add    $0x10,%esp
  af:	89 45 e0             	mov    %eax,-0x20(%ebp)
  goodcalls = getnumsyscallsgood(swag);
  b2:	83 ec 0c             	sub    $0xc,%esp
  b5:	ff 75 e4             	pushl  -0x1c(%ebp)
  b8:	e8 56 03 00 00       	call   413 <getnumsyscallsgood>
  bd:	83 c4 10             	add    $0x10,%esp
  c0:	89 45 dc             	mov    %eax,-0x24(%ebp)
  //calls--;
  goodcalls = calls - goodcalls; 
  c3:	8b 45 e0             	mov    -0x20(%ebp),%eax
  c6:	2b 45 dc             	sub    -0x24(%ebp),%eax
  c9:	89 45 dc             	mov    %eax,-0x24(%ebp)
  printf(1, "%d, %d\n", calls, goodcalls);
  cc:	ff 75 dc             	pushl  -0x24(%ebp)
  cf:	ff 75 e0             	pushl  -0x20(%ebp)
  d2:	68 be 08 00 00       	push   $0x8be
  d7:	6a 01                	push   $0x1
  d9:	e8 19 04 00 00       	call   4f7 <printf>
  de:	83 c4 10             	add    $0x10,%esp
    
  return(0);
  e1:	b8 00 00 00 00       	mov    $0x0,%eax
}
  e6:	8d 65 f8             	lea    -0x8(%ebp),%esp
  e9:	59                   	pop    %ecx
  ea:	5b                   	pop    %ebx
  eb:	5d                   	pop    %ebp
  ec:	8d 61 fc             	lea    -0x4(%ecx),%esp
  ef:	c3                   	ret    

000000f0 <stosb>:
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{
  f0:	55                   	push   %ebp
  f1:	89 e5                	mov    %esp,%ebp
  f3:	57                   	push   %edi
  f4:	53                   	push   %ebx
  asm volatile("cld; rep stosb" :
  f5:	8b 4d 08             	mov    0x8(%ebp),%ecx
  f8:	8b 55 10             	mov    0x10(%ebp),%edx
  fb:	8b 45 0c             	mov    0xc(%ebp),%eax
  fe:	89 cb                	mov    %ecx,%ebx
 100:	89 df                	mov    %ebx,%edi
 102:	89 d1                	mov    %edx,%ecx
 104:	fc                   	cld    
 105:	f3 aa                	rep stos %al,%es:(%edi)
 107:	89 ca                	mov    %ecx,%edx
 109:	89 fb                	mov    %edi,%ebx
 10b:	89 5d 08             	mov    %ebx,0x8(%ebp)
 10e:	89 55 10             	mov    %edx,0x10(%ebp)
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}
 111:	90                   	nop
 112:	5b                   	pop    %ebx
 113:	5f                   	pop    %edi
 114:	5d                   	pop    %ebp
 115:	c3                   	ret    

00000116 <strcpy>:
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
 116:	f3 0f 1e fb          	endbr32 
 11a:	55                   	push   %ebp
 11b:	89 e5                	mov    %esp,%ebp
 11d:	83 ec 10             	sub    $0x10,%esp
  char *os;

  os = s;
 120:	8b 45 08             	mov    0x8(%ebp),%eax
 123:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while((*s++ = *t++) != 0)
 126:	90                   	nop
 127:	8b 55 0c             	mov    0xc(%ebp),%edx
 12a:	8d 42 01             	lea    0x1(%edx),%eax
 12d:	89 45 0c             	mov    %eax,0xc(%ebp)
 130:	8b 45 08             	mov    0x8(%ebp),%eax
 133:	8d 48 01             	lea    0x1(%eax),%ecx
 136:	89 4d 08             	mov    %ecx,0x8(%ebp)
 139:	0f b6 12             	movzbl (%edx),%edx
 13c:	88 10                	mov    %dl,(%eax)
 13e:	0f b6 00             	movzbl (%eax),%eax
 141:	84 c0                	test   %al,%al
 143:	75 e2                	jne    127 <strcpy+0x11>
    ;
  return os;
 145:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 148:	c9                   	leave  
 149:	c3                   	ret    

0000014a <strcmp>:

int
strcmp(const char *p, const char *q)
{
 14a:	f3 0f 1e fb          	endbr32 
 14e:	55                   	push   %ebp
 14f:	89 e5                	mov    %esp,%ebp
  while(*p && *p == *q)
 151:	eb 08                	jmp    15b <strcmp+0x11>
    p++, q++;
 153:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 157:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
  while(*p && *p == *q)
 15b:	8b 45 08             	mov    0x8(%ebp),%eax
 15e:	0f b6 00             	movzbl (%eax),%eax
 161:	84 c0                	test   %al,%al
 163:	74 10                	je     175 <strcmp+0x2b>
 165:	8b 45 08             	mov    0x8(%ebp),%eax
 168:	0f b6 10             	movzbl (%eax),%edx
 16b:	8b 45 0c             	mov    0xc(%ebp),%eax
 16e:	0f b6 00             	movzbl (%eax),%eax
 171:	38 c2                	cmp    %al,%dl
 173:	74 de                	je     153 <strcmp+0x9>
  return (uchar)*p - (uchar)*q;
 175:	8b 45 08             	mov    0x8(%ebp),%eax
 178:	0f b6 00             	movzbl (%eax),%eax
 17b:	0f b6 d0             	movzbl %al,%edx
 17e:	8b 45 0c             	mov    0xc(%ebp),%eax
 181:	0f b6 00             	movzbl (%eax),%eax
 184:	0f b6 c0             	movzbl %al,%eax
 187:	29 c2                	sub    %eax,%edx
 189:	89 d0                	mov    %edx,%eax
}
 18b:	5d                   	pop    %ebp
 18c:	c3                   	ret    

0000018d <strlen>:

uint
strlen(const char *s)
{
 18d:	f3 0f 1e fb          	endbr32 
 191:	55                   	push   %ebp
 192:	89 e5                	mov    %esp,%ebp
 194:	83 ec 10             	sub    $0x10,%esp
  int n;

  for(n = 0; s[n]; n++)
 197:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
 19e:	eb 04                	jmp    1a4 <strlen+0x17>
 1a0:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 1a4:	8b 55 fc             	mov    -0x4(%ebp),%edx
 1a7:	8b 45 08             	mov    0x8(%ebp),%eax
 1aa:	01 d0                	add    %edx,%eax
 1ac:	0f b6 00             	movzbl (%eax),%eax
 1af:	84 c0                	test   %al,%al
 1b1:	75 ed                	jne    1a0 <strlen+0x13>
    ;
  return n;
 1b3:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 1b6:	c9                   	leave  
 1b7:	c3                   	ret    

000001b8 <memset>:

void*
memset(void *dst, int c, uint n)
{
 1b8:	f3 0f 1e fb          	endbr32 
 1bc:	55                   	push   %ebp
 1bd:	89 e5                	mov    %esp,%ebp
  stosb(dst, c, n);
 1bf:	8b 45 10             	mov    0x10(%ebp),%eax
 1c2:	50                   	push   %eax
 1c3:	ff 75 0c             	pushl  0xc(%ebp)
 1c6:	ff 75 08             	pushl  0x8(%ebp)
 1c9:	e8 22 ff ff ff       	call   f0 <stosb>
 1ce:	83 c4 0c             	add    $0xc,%esp
  return dst;
 1d1:	8b 45 08             	mov    0x8(%ebp),%eax
}
 1d4:	c9                   	leave  
 1d5:	c3                   	ret    

000001d6 <strchr>:

char*
strchr(const char *s, char c)
{
 1d6:	f3 0f 1e fb          	endbr32 
 1da:	55                   	push   %ebp
 1db:	89 e5                	mov    %esp,%ebp
 1dd:	83 ec 04             	sub    $0x4,%esp
 1e0:	8b 45 0c             	mov    0xc(%ebp),%eax
 1e3:	88 45 fc             	mov    %al,-0x4(%ebp)
  for(; *s; s++)
 1e6:	eb 14                	jmp    1fc <strchr+0x26>
    if(*s == c)
 1e8:	8b 45 08             	mov    0x8(%ebp),%eax
 1eb:	0f b6 00             	movzbl (%eax),%eax
 1ee:	38 45 fc             	cmp    %al,-0x4(%ebp)
 1f1:	75 05                	jne    1f8 <strchr+0x22>
      return (char*)s;
 1f3:	8b 45 08             	mov    0x8(%ebp),%eax
 1f6:	eb 13                	jmp    20b <strchr+0x35>
  for(; *s; s++)
 1f8:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 1fc:	8b 45 08             	mov    0x8(%ebp),%eax
 1ff:	0f b6 00             	movzbl (%eax),%eax
 202:	84 c0                	test   %al,%al
 204:	75 e2                	jne    1e8 <strchr+0x12>
  return 0;
 206:	b8 00 00 00 00       	mov    $0x0,%eax
}
 20b:	c9                   	leave  
 20c:	c3                   	ret    

0000020d <gets>:

char*
gets(char *buf, int max)
{
 20d:	f3 0f 1e fb          	endbr32 
 211:	55                   	push   %ebp
 212:	89 e5                	mov    %esp,%ebp
 214:	83 ec 18             	sub    $0x18,%esp
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 217:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 21e:	eb 42                	jmp    262 <gets+0x55>
    cc = read(0, &c, 1);
 220:	83 ec 04             	sub    $0x4,%esp
 223:	6a 01                	push   $0x1
 225:	8d 45 ef             	lea    -0x11(%ebp),%eax
 228:	50                   	push   %eax
 229:	6a 00                	push   $0x0
 22b:	e8 53 01 00 00       	call   383 <read>
 230:	83 c4 10             	add    $0x10,%esp
 233:	89 45 f0             	mov    %eax,-0x10(%ebp)
    if(cc < 1)
 236:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 23a:	7e 33                	jle    26f <gets+0x62>
      break;
    buf[i++] = c;
 23c:	8b 45 f4             	mov    -0xc(%ebp),%eax
 23f:	8d 50 01             	lea    0x1(%eax),%edx
 242:	89 55 f4             	mov    %edx,-0xc(%ebp)
 245:	89 c2                	mov    %eax,%edx
 247:	8b 45 08             	mov    0x8(%ebp),%eax
 24a:	01 c2                	add    %eax,%edx
 24c:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 250:	88 02                	mov    %al,(%edx)
    if(c == '\n' || c == '\r')
 252:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 256:	3c 0a                	cmp    $0xa,%al
 258:	74 16                	je     270 <gets+0x63>
 25a:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 25e:	3c 0d                	cmp    $0xd,%al
 260:	74 0e                	je     270 <gets+0x63>
  for(i=0; i+1 < max; ){
 262:	8b 45 f4             	mov    -0xc(%ebp),%eax
 265:	83 c0 01             	add    $0x1,%eax
 268:	39 45 0c             	cmp    %eax,0xc(%ebp)
 26b:	7f b3                	jg     220 <gets+0x13>
 26d:	eb 01                	jmp    270 <gets+0x63>
      break;
 26f:	90                   	nop
      break;
  }
  buf[i] = '\0';
 270:	8b 55 f4             	mov    -0xc(%ebp),%edx
 273:	8b 45 08             	mov    0x8(%ebp),%eax
 276:	01 d0                	add    %edx,%eax
 278:	c6 00 00             	movb   $0x0,(%eax)
  return buf;
 27b:	8b 45 08             	mov    0x8(%ebp),%eax
}
 27e:	c9                   	leave  
 27f:	c3                   	ret    

00000280 <stat>:

int
stat(const char *n, struct stat *st)
{
 280:	f3 0f 1e fb          	endbr32 
 284:	55                   	push   %ebp
 285:	89 e5                	mov    %esp,%ebp
 287:	83 ec 18             	sub    $0x18,%esp
  int fd;
  int r;

  fd = open(n, O_RDONLY);
 28a:	83 ec 08             	sub    $0x8,%esp
 28d:	6a 00                	push   $0x0
 28f:	ff 75 08             	pushl  0x8(%ebp)
 292:	e8 14 01 00 00       	call   3ab <open>
 297:	83 c4 10             	add    $0x10,%esp
 29a:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(fd < 0)
 29d:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 2a1:	79 07                	jns    2aa <stat+0x2a>
    return -1;
 2a3:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 2a8:	eb 25                	jmp    2cf <stat+0x4f>
  r = fstat(fd, st);
 2aa:	83 ec 08             	sub    $0x8,%esp
 2ad:	ff 75 0c             	pushl  0xc(%ebp)
 2b0:	ff 75 f4             	pushl  -0xc(%ebp)
 2b3:	e8 0b 01 00 00       	call   3c3 <fstat>
 2b8:	83 c4 10             	add    $0x10,%esp
 2bb:	89 45 f0             	mov    %eax,-0x10(%ebp)
  close(fd);
 2be:	83 ec 0c             	sub    $0xc,%esp
 2c1:	ff 75 f4             	pushl  -0xc(%ebp)
 2c4:	e8 ca 00 00 00       	call   393 <close>
 2c9:	83 c4 10             	add    $0x10,%esp
  return r;
 2cc:	8b 45 f0             	mov    -0x10(%ebp),%eax
}
 2cf:	c9                   	leave  
 2d0:	c3                   	ret    

000002d1 <atoi>:

int
atoi(const char *s)
{
 2d1:	f3 0f 1e fb          	endbr32 
 2d5:	55                   	push   %ebp
 2d6:	89 e5                	mov    %esp,%ebp
 2d8:	83 ec 10             	sub    $0x10,%esp
  int n;

  n = 0;
 2db:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 2e2:	eb 25                	jmp    309 <atoi+0x38>
    n = n*10 + *s++ - '0';
 2e4:	8b 55 fc             	mov    -0x4(%ebp),%edx
 2e7:	89 d0                	mov    %edx,%eax
 2e9:	c1 e0 02             	shl    $0x2,%eax
 2ec:	01 d0                	add    %edx,%eax
 2ee:	01 c0                	add    %eax,%eax
 2f0:	89 c1                	mov    %eax,%ecx
 2f2:	8b 45 08             	mov    0x8(%ebp),%eax
 2f5:	8d 50 01             	lea    0x1(%eax),%edx
 2f8:	89 55 08             	mov    %edx,0x8(%ebp)
 2fb:	0f b6 00             	movzbl (%eax),%eax
 2fe:	0f be c0             	movsbl %al,%eax
 301:	01 c8                	add    %ecx,%eax
 303:	83 e8 30             	sub    $0x30,%eax
 306:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 309:	8b 45 08             	mov    0x8(%ebp),%eax
 30c:	0f b6 00             	movzbl (%eax),%eax
 30f:	3c 2f                	cmp    $0x2f,%al
 311:	7e 0a                	jle    31d <atoi+0x4c>
 313:	8b 45 08             	mov    0x8(%ebp),%eax
 316:	0f b6 00             	movzbl (%eax),%eax
 319:	3c 39                	cmp    $0x39,%al
 31b:	7e c7                	jle    2e4 <atoi+0x13>
  return n;
 31d:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 320:	c9                   	leave  
 321:	c3                   	ret    

00000322 <memmove>:

void*
memmove(void *vdst, const void *vsrc, int n)
{
 322:	f3 0f 1e fb          	endbr32 
 326:	55                   	push   %ebp
 327:	89 e5                	mov    %esp,%ebp
 329:	83 ec 10             	sub    $0x10,%esp
  char *dst;
  const char *src;

  dst = vdst;
 32c:	8b 45 08             	mov    0x8(%ebp),%eax
 32f:	89 45 fc             	mov    %eax,-0x4(%ebp)
  src = vsrc;
 332:	8b 45 0c             	mov    0xc(%ebp),%eax
 335:	89 45 f8             	mov    %eax,-0x8(%ebp)
  while(n-- > 0)
 338:	eb 17                	jmp    351 <memmove+0x2f>
    *dst++ = *src++;
 33a:	8b 55 f8             	mov    -0x8(%ebp),%edx
 33d:	8d 42 01             	lea    0x1(%edx),%eax
 340:	89 45 f8             	mov    %eax,-0x8(%ebp)
 343:	8b 45 fc             	mov    -0x4(%ebp),%eax
 346:	8d 48 01             	lea    0x1(%eax),%ecx
 349:	89 4d fc             	mov    %ecx,-0x4(%ebp)
 34c:	0f b6 12             	movzbl (%edx),%edx
 34f:	88 10                	mov    %dl,(%eax)
  while(n-- > 0)
 351:	8b 45 10             	mov    0x10(%ebp),%eax
 354:	8d 50 ff             	lea    -0x1(%eax),%edx
 357:	89 55 10             	mov    %edx,0x10(%ebp)
 35a:	85 c0                	test   %eax,%eax
 35c:	7f dc                	jg     33a <memmove+0x18>
  return vdst;
 35e:	8b 45 08             	mov    0x8(%ebp),%eax
}
 361:	c9                   	leave  
 362:	c3                   	ret    

00000363 <fork>:
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
 363:	b8 01 00 00 00       	mov    $0x1,%eax
 368:	cd 40                	int    $0x40
 36a:	c3                   	ret    

0000036b <exit>:
SYSCALL(exit)
 36b:	b8 02 00 00 00       	mov    $0x2,%eax
 370:	cd 40                	int    $0x40
 372:	c3                   	ret    

00000373 <wait>:
SYSCALL(wait)
 373:	b8 03 00 00 00       	mov    $0x3,%eax
 378:	cd 40                	int    $0x40
 37a:	c3                   	ret    

0000037b <pipe>:
SYSCALL(pipe)
 37b:	b8 04 00 00 00       	mov    $0x4,%eax
 380:	cd 40                	int    $0x40
 382:	c3                   	ret    

00000383 <read>:
SYSCALL(read)
 383:	b8 05 00 00 00       	mov    $0x5,%eax
 388:	cd 40                	int    $0x40
 38a:	c3                   	ret    

0000038b <write>:
SYSCALL(write)
 38b:	b8 10 00 00 00       	mov    $0x10,%eax
 390:	cd 40                	int    $0x40
 392:	c3                   	ret    

00000393 <close>:
SYSCALL(close)
 393:	b8 15 00 00 00       	mov    $0x15,%eax
 398:	cd 40                	int    $0x40
 39a:	c3                   	ret    

0000039b <kill>:
SYSCALL(kill)
 39b:	b8 06 00 00 00       	mov    $0x6,%eax
 3a0:	cd 40                	int    $0x40
 3a2:	c3                   	ret    

000003a3 <exec>:
SYSCALL(exec)
 3a3:	b8 07 00 00 00       	mov    $0x7,%eax
 3a8:	cd 40                	int    $0x40
 3aa:	c3                   	ret    

000003ab <open>:
SYSCALL(open)
 3ab:	b8 0f 00 00 00       	mov    $0xf,%eax
 3b0:	cd 40                	int    $0x40
 3b2:	c3                   	ret    

000003b3 <mknod>:
SYSCALL(mknod)
 3b3:	b8 11 00 00 00       	mov    $0x11,%eax
 3b8:	cd 40                	int    $0x40
 3ba:	c3                   	ret    

000003bb <unlink>:
SYSCALL(unlink)
 3bb:	b8 12 00 00 00       	mov    $0x12,%eax
 3c0:	cd 40                	int    $0x40
 3c2:	c3                   	ret    

000003c3 <fstat>:
SYSCALL(fstat)
 3c3:	b8 08 00 00 00       	mov    $0x8,%eax
 3c8:	cd 40                	int    $0x40
 3ca:	c3                   	ret    

000003cb <link>:
SYSCALL(link)
 3cb:	b8 13 00 00 00       	mov    $0x13,%eax
 3d0:	cd 40                	int    $0x40
 3d2:	c3                   	ret    

000003d3 <mkdir>:
SYSCALL(mkdir)
 3d3:	b8 14 00 00 00       	mov    $0x14,%eax
 3d8:	cd 40                	int    $0x40
 3da:	c3                   	ret    

000003db <chdir>:
SYSCALL(chdir)
 3db:	b8 09 00 00 00       	mov    $0x9,%eax
 3e0:	cd 40                	int    $0x40
 3e2:	c3                   	ret    

000003e3 <dup>:
SYSCALL(dup)
 3e3:	b8 0a 00 00 00       	mov    $0xa,%eax
 3e8:	cd 40                	int    $0x40
 3ea:	c3                   	ret    

000003eb <getpid>:
SYSCALL(getpid)
 3eb:	b8 0b 00 00 00       	mov    $0xb,%eax
 3f0:	cd 40                	int    $0x40
 3f2:	c3                   	ret    

000003f3 <sbrk>:
SYSCALL(sbrk)
 3f3:	b8 0c 00 00 00       	mov    $0xc,%eax
 3f8:	cd 40                	int    $0x40
 3fa:	c3                   	ret    

000003fb <sleep>:
SYSCALL(sleep)
 3fb:	b8 0d 00 00 00       	mov    $0xd,%eax
 400:	cd 40                	int    $0x40
 402:	c3                   	ret    

00000403 <uptime>:
SYSCALL(uptime)
 403:	b8 0e 00 00 00       	mov    $0xe,%eax
 408:	cd 40                	int    $0x40
 40a:	c3                   	ret    

0000040b <getnumsyscalls>:
SYSCALL(getnumsyscalls)
 40b:	b8 16 00 00 00       	mov    $0x16,%eax
 410:	cd 40                	int    $0x40
 412:	c3                   	ret    

00000413 <getnumsyscallsgood>:
SYSCALL(getnumsyscallsgood)
 413:	b8 17 00 00 00       	mov    $0x17,%eax
 418:	cd 40                	int    $0x40
 41a:	c3                   	ret    

0000041b <putc>:
#include "stat.h"
#include "user.h"

static void
putc(int fd, char c)
{
 41b:	f3 0f 1e fb          	endbr32 
 41f:	55                   	push   %ebp
 420:	89 e5                	mov    %esp,%ebp
 422:	83 ec 18             	sub    $0x18,%esp
 425:	8b 45 0c             	mov    0xc(%ebp),%eax
 428:	88 45 f4             	mov    %al,-0xc(%ebp)
  write(fd, &c, 1);
 42b:	83 ec 04             	sub    $0x4,%esp
 42e:	6a 01                	push   $0x1
 430:	8d 45 f4             	lea    -0xc(%ebp),%eax
 433:	50                   	push   %eax
 434:	ff 75 08             	pushl  0x8(%ebp)
 437:	e8 4f ff ff ff       	call   38b <write>
 43c:	83 c4 10             	add    $0x10,%esp
}
 43f:	90                   	nop
 440:	c9                   	leave  
 441:	c3                   	ret    

00000442 <printint>:

static void
printint(int fd, int xx, int base, int sgn)
{
 442:	f3 0f 1e fb          	endbr32 
 446:	55                   	push   %ebp
 447:	89 e5                	mov    %esp,%ebp
 449:	83 ec 28             	sub    $0x28,%esp
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
 44c:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  if(sgn && xx < 0){
 453:	83 7d 14 00          	cmpl   $0x0,0x14(%ebp)
 457:	74 17                	je     470 <printint+0x2e>
 459:	83 7d 0c 00          	cmpl   $0x0,0xc(%ebp)
 45d:	79 11                	jns    470 <printint+0x2e>
    neg = 1;
 45f:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
    x = -xx;
 466:	8b 45 0c             	mov    0xc(%ebp),%eax
 469:	f7 d8                	neg    %eax
 46b:	89 45 ec             	mov    %eax,-0x14(%ebp)
 46e:	eb 06                	jmp    476 <printint+0x34>
  } else {
    x = xx;
 470:	8b 45 0c             	mov    0xc(%ebp),%eax
 473:	89 45 ec             	mov    %eax,-0x14(%ebp)
  }

  i = 0;
 476:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  do{
    buf[i++] = digits[x % base];
 47d:	8b 4d 10             	mov    0x10(%ebp),%ecx
 480:	8b 45 ec             	mov    -0x14(%ebp),%eax
 483:	ba 00 00 00 00       	mov    $0x0,%edx
 488:	f7 f1                	div    %ecx
 48a:	89 d1                	mov    %edx,%ecx
 48c:	8b 45 f4             	mov    -0xc(%ebp),%eax
 48f:	8d 50 01             	lea    0x1(%eax),%edx
 492:	89 55 f4             	mov    %edx,-0xc(%ebp)
 495:	0f b6 91 24 0b 00 00 	movzbl 0xb24(%ecx),%edx
 49c:	88 54 05 dc          	mov    %dl,-0x24(%ebp,%eax,1)
  }while((x /= base) != 0);
 4a0:	8b 4d 10             	mov    0x10(%ebp),%ecx
 4a3:	8b 45 ec             	mov    -0x14(%ebp),%eax
 4a6:	ba 00 00 00 00       	mov    $0x0,%edx
 4ab:	f7 f1                	div    %ecx
 4ad:	89 45 ec             	mov    %eax,-0x14(%ebp)
 4b0:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 4b4:	75 c7                	jne    47d <printint+0x3b>
  if(neg)
 4b6:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 4ba:	74 2d                	je     4e9 <printint+0xa7>
    buf[i++] = '-';
 4bc:	8b 45 f4             	mov    -0xc(%ebp),%eax
 4bf:	8d 50 01             	lea    0x1(%eax),%edx
 4c2:	89 55 f4             	mov    %edx,-0xc(%ebp)
 4c5:	c6 44 05 dc 2d       	movb   $0x2d,-0x24(%ebp,%eax,1)

  while(--i >= 0)
 4ca:	eb 1d                	jmp    4e9 <printint+0xa7>
    putc(fd, buf[i]);
 4cc:	8d 55 dc             	lea    -0x24(%ebp),%edx
 4cf:	8b 45 f4             	mov    -0xc(%ebp),%eax
 4d2:	01 d0                	add    %edx,%eax
 4d4:	0f b6 00             	movzbl (%eax),%eax
 4d7:	0f be c0             	movsbl %al,%eax
 4da:	83 ec 08             	sub    $0x8,%esp
 4dd:	50                   	push   %eax
 4de:	ff 75 08             	pushl  0x8(%ebp)
 4e1:	e8 35 ff ff ff       	call   41b <putc>
 4e6:	83 c4 10             	add    $0x10,%esp
  while(--i >= 0)
 4e9:	83 6d f4 01          	subl   $0x1,-0xc(%ebp)
 4ed:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 4f1:	79 d9                	jns    4cc <printint+0x8a>
}
 4f3:	90                   	nop
 4f4:	90                   	nop
 4f5:	c9                   	leave  
 4f6:	c3                   	ret    

000004f7 <printf>:

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, const char *fmt, ...)
{
 4f7:	f3 0f 1e fb          	endbr32 
 4fb:	55                   	push   %ebp
 4fc:	89 e5                	mov    %esp,%ebp
 4fe:	83 ec 28             	sub    $0x28,%esp
  char *s;
  int c, i, state;
  uint *ap;

  state = 0;
 501:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  ap = (uint*)(void*)&fmt + 1;
 508:	8d 45 0c             	lea    0xc(%ebp),%eax
 50b:	83 c0 04             	add    $0x4,%eax
 50e:	89 45 e8             	mov    %eax,-0x18(%ebp)
  for(i = 0; fmt[i]; i++){
 511:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 518:	e9 59 01 00 00       	jmp    676 <printf+0x17f>
    c = fmt[i] & 0xff;
 51d:	8b 55 0c             	mov    0xc(%ebp),%edx
 520:	8b 45 f0             	mov    -0x10(%ebp),%eax
 523:	01 d0                	add    %edx,%eax
 525:	0f b6 00             	movzbl (%eax),%eax
 528:	0f be c0             	movsbl %al,%eax
 52b:	25 ff 00 00 00       	and    $0xff,%eax
 530:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    if(state == 0){
 533:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 537:	75 2c                	jne    565 <printf+0x6e>
      if(c == '%'){
 539:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 53d:	75 0c                	jne    54b <printf+0x54>
        state = '%';
 53f:	c7 45 ec 25 00 00 00 	movl   $0x25,-0x14(%ebp)
 546:	e9 27 01 00 00       	jmp    672 <printf+0x17b>
      } else {
        putc(fd, c);
 54b:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 54e:	0f be c0             	movsbl %al,%eax
 551:	83 ec 08             	sub    $0x8,%esp
 554:	50                   	push   %eax
 555:	ff 75 08             	pushl  0x8(%ebp)
 558:	e8 be fe ff ff       	call   41b <putc>
 55d:	83 c4 10             	add    $0x10,%esp
 560:	e9 0d 01 00 00       	jmp    672 <printf+0x17b>
      }
    } else if(state == '%'){
 565:	83 7d ec 25          	cmpl   $0x25,-0x14(%ebp)
 569:	0f 85 03 01 00 00    	jne    672 <printf+0x17b>
      if(c == 'd'){
 56f:	83 7d e4 64          	cmpl   $0x64,-0x1c(%ebp)
 573:	75 1e                	jne    593 <printf+0x9c>
        printint(fd, *ap, 10, 1);
 575:	8b 45 e8             	mov    -0x18(%ebp),%eax
 578:	8b 00                	mov    (%eax),%eax
 57a:	6a 01                	push   $0x1
 57c:	6a 0a                	push   $0xa
 57e:	50                   	push   %eax
 57f:	ff 75 08             	pushl  0x8(%ebp)
 582:	e8 bb fe ff ff       	call   442 <printint>
 587:	83 c4 10             	add    $0x10,%esp
        ap++;
 58a:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 58e:	e9 d8 00 00 00       	jmp    66b <printf+0x174>
      } else if(c == 'x' || c == 'p'){
 593:	83 7d e4 78          	cmpl   $0x78,-0x1c(%ebp)
 597:	74 06                	je     59f <printf+0xa8>
 599:	83 7d e4 70          	cmpl   $0x70,-0x1c(%ebp)
 59d:	75 1e                	jne    5bd <printf+0xc6>
        printint(fd, *ap, 16, 0);
 59f:	8b 45 e8             	mov    -0x18(%ebp),%eax
 5a2:	8b 00                	mov    (%eax),%eax
 5a4:	6a 00                	push   $0x0
 5a6:	6a 10                	push   $0x10
 5a8:	50                   	push   %eax
 5a9:	ff 75 08             	pushl  0x8(%ebp)
 5ac:	e8 91 fe ff ff       	call   442 <printint>
 5b1:	83 c4 10             	add    $0x10,%esp
        ap++;
 5b4:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 5b8:	e9 ae 00 00 00       	jmp    66b <printf+0x174>
      } else if(c == 's'){
 5bd:	83 7d e4 73          	cmpl   $0x73,-0x1c(%ebp)
 5c1:	75 43                	jne    606 <printf+0x10f>
        s = (char*)*ap;
 5c3:	8b 45 e8             	mov    -0x18(%ebp),%eax
 5c6:	8b 00                	mov    (%eax),%eax
 5c8:	89 45 f4             	mov    %eax,-0xc(%ebp)
        ap++;
 5cb:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
        if(s == 0)
 5cf:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 5d3:	75 25                	jne    5fa <printf+0x103>
          s = "(null)";
 5d5:	c7 45 f4 c6 08 00 00 	movl   $0x8c6,-0xc(%ebp)
        while(*s != 0){
 5dc:	eb 1c                	jmp    5fa <printf+0x103>
          putc(fd, *s);
 5de:	8b 45 f4             	mov    -0xc(%ebp),%eax
 5e1:	0f b6 00             	movzbl (%eax),%eax
 5e4:	0f be c0             	movsbl %al,%eax
 5e7:	83 ec 08             	sub    $0x8,%esp
 5ea:	50                   	push   %eax
 5eb:	ff 75 08             	pushl  0x8(%ebp)
 5ee:	e8 28 fe ff ff       	call   41b <putc>
 5f3:	83 c4 10             	add    $0x10,%esp
          s++;
 5f6:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
        while(*s != 0){
 5fa:	8b 45 f4             	mov    -0xc(%ebp),%eax
 5fd:	0f b6 00             	movzbl (%eax),%eax
 600:	84 c0                	test   %al,%al
 602:	75 da                	jne    5de <printf+0xe7>
 604:	eb 65                	jmp    66b <printf+0x174>
        }
      } else if(c == 'c'){
 606:	83 7d e4 63          	cmpl   $0x63,-0x1c(%ebp)
 60a:	75 1d                	jne    629 <printf+0x132>
        putc(fd, *ap);
 60c:	8b 45 e8             	mov    -0x18(%ebp),%eax
 60f:	8b 00                	mov    (%eax),%eax
 611:	0f be c0             	movsbl %al,%eax
 614:	83 ec 08             	sub    $0x8,%esp
 617:	50                   	push   %eax
 618:	ff 75 08             	pushl  0x8(%ebp)
 61b:	e8 fb fd ff ff       	call   41b <putc>
 620:	83 c4 10             	add    $0x10,%esp
        ap++;
 623:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 627:	eb 42                	jmp    66b <printf+0x174>
      } else if(c == '%'){
 629:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 62d:	75 17                	jne    646 <printf+0x14f>
        putc(fd, c);
 62f:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 632:	0f be c0             	movsbl %al,%eax
 635:	83 ec 08             	sub    $0x8,%esp
 638:	50                   	push   %eax
 639:	ff 75 08             	pushl  0x8(%ebp)
 63c:	e8 da fd ff ff       	call   41b <putc>
 641:	83 c4 10             	add    $0x10,%esp
 644:	eb 25                	jmp    66b <printf+0x174>
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
 646:	83 ec 08             	sub    $0x8,%esp
 649:	6a 25                	push   $0x25
 64b:	ff 75 08             	pushl  0x8(%ebp)
 64e:	e8 c8 fd ff ff       	call   41b <putc>
 653:	83 c4 10             	add    $0x10,%esp
        putc(fd, c);
 656:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 659:	0f be c0             	movsbl %al,%eax
 65c:	83 ec 08             	sub    $0x8,%esp
 65f:	50                   	push   %eax
 660:	ff 75 08             	pushl  0x8(%ebp)
 663:	e8 b3 fd ff ff       	call   41b <putc>
 668:	83 c4 10             	add    $0x10,%esp
      }
      state = 0;
 66b:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  for(i = 0; fmt[i]; i++){
 672:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 676:	8b 55 0c             	mov    0xc(%ebp),%edx
 679:	8b 45 f0             	mov    -0x10(%ebp),%eax
 67c:	01 d0                	add    %edx,%eax
 67e:	0f b6 00             	movzbl (%eax),%eax
 681:	84 c0                	test   %al,%al
 683:	0f 85 94 fe ff ff    	jne    51d <printf+0x26>
    }
  }
}
 689:	90                   	nop
 68a:	90                   	nop
 68b:	c9                   	leave  
 68c:	c3                   	ret    

0000068d <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
 68d:	f3 0f 1e fb          	endbr32 
 691:	55                   	push   %ebp
 692:	89 e5                	mov    %esp,%ebp
 694:	83 ec 10             	sub    $0x10,%esp
  Header *bp, *p;

  bp = (Header*)ap - 1;
 697:	8b 45 08             	mov    0x8(%ebp),%eax
 69a:	83 e8 08             	sub    $0x8,%eax
 69d:	89 45 f8             	mov    %eax,-0x8(%ebp)
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 6a0:	a1 40 0b 00 00       	mov    0xb40,%eax
 6a5:	89 45 fc             	mov    %eax,-0x4(%ebp)
 6a8:	eb 24                	jmp    6ce <free+0x41>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
 6aa:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6ad:	8b 00                	mov    (%eax),%eax
 6af:	39 45 fc             	cmp    %eax,-0x4(%ebp)
 6b2:	72 12                	jb     6c6 <free+0x39>
 6b4:	8b 45 f8             	mov    -0x8(%ebp),%eax
 6b7:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 6ba:	77 24                	ja     6e0 <free+0x53>
 6bc:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6bf:	8b 00                	mov    (%eax),%eax
 6c1:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 6c4:	72 1a                	jb     6e0 <free+0x53>
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 6c6:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6c9:	8b 00                	mov    (%eax),%eax
 6cb:	89 45 fc             	mov    %eax,-0x4(%ebp)
 6ce:	8b 45 f8             	mov    -0x8(%ebp),%eax
 6d1:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 6d4:	76 d4                	jbe    6aa <free+0x1d>
 6d6:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6d9:	8b 00                	mov    (%eax),%eax
 6db:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 6de:	73 ca                	jae    6aa <free+0x1d>
      break;
  if(bp + bp->s.size == p->s.ptr){
 6e0:	8b 45 f8             	mov    -0x8(%ebp),%eax
 6e3:	8b 40 04             	mov    0x4(%eax),%eax
 6e6:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 6ed:	8b 45 f8             	mov    -0x8(%ebp),%eax
 6f0:	01 c2                	add    %eax,%edx
 6f2:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6f5:	8b 00                	mov    (%eax),%eax
 6f7:	39 c2                	cmp    %eax,%edx
 6f9:	75 24                	jne    71f <free+0x92>
    bp->s.size += p->s.ptr->s.size;
 6fb:	8b 45 f8             	mov    -0x8(%ebp),%eax
 6fe:	8b 50 04             	mov    0x4(%eax),%edx
 701:	8b 45 fc             	mov    -0x4(%ebp),%eax
 704:	8b 00                	mov    (%eax),%eax
 706:	8b 40 04             	mov    0x4(%eax),%eax
 709:	01 c2                	add    %eax,%edx
 70b:	8b 45 f8             	mov    -0x8(%ebp),%eax
 70e:	89 50 04             	mov    %edx,0x4(%eax)
    bp->s.ptr = p->s.ptr->s.ptr;
 711:	8b 45 fc             	mov    -0x4(%ebp),%eax
 714:	8b 00                	mov    (%eax),%eax
 716:	8b 10                	mov    (%eax),%edx
 718:	8b 45 f8             	mov    -0x8(%ebp),%eax
 71b:	89 10                	mov    %edx,(%eax)
 71d:	eb 0a                	jmp    729 <free+0x9c>
  } else
    bp->s.ptr = p->s.ptr;
 71f:	8b 45 fc             	mov    -0x4(%ebp),%eax
 722:	8b 10                	mov    (%eax),%edx
 724:	8b 45 f8             	mov    -0x8(%ebp),%eax
 727:	89 10                	mov    %edx,(%eax)
  if(p + p->s.size == bp){
 729:	8b 45 fc             	mov    -0x4(%ebp),%eax
 72c:	8b 40 04             	mov    0x4(%eax),%eax
 72f:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 736:	8b 45 fc             	mov    -0x4(%ebp),%eax
 739:	01 d0                	add    %edx,%eax
 73b:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 73e:	75 20                	jne    760 <free+0xd3>
    p->s.size += bp->s.size;
 740:	8b 45 fc             	mov    -0x4(%ebp),%eax
 743:	8b 50 04             	mov    0x4(%eax),%edx
 746:	8b 45 f8             	mov    -0x8(%ebp),%eax
 749:	8b 40 04             	mov    0x4(%eax),%eax
 74c:	01 c2                	add    %eax,%edx
 74e:	8b 45 fc             	mov    -0x4(%ebp),%eax
 751:	89 50 04             	mov    %edx,0x4(%eax)
    p->s.ptr = bp->s.ptr;
 754:	8b 45 f8             	mov    -0x8(%ebp),%eax
 757:	8b 10                	mov    (%eax),%edx
 759:	8b 45 fc             	mov    -0x4(%ebp),%eax
 75c:	89 10                	mov    %edx,(%eax)
 75e:	eb 08                	jmp    768 <free+0xdb>
  } else
    p->s.ptr = bp;
 760:	8b 45 fc             	mov    -0x4(%ebp),%eax
 763:	8b 55 f8             	mov    -0x8(%ebp),%edx
 766:	89 10                	mov    %edx,(%eax)
  freep = p;
 768:	8b 45 fc             	mov    -0x4(%ebp),%eax
 76b:	a3 40 0b 00 00       	mov    %eax,0xb40
}
 770:	90                   	nop
 771:	c9                   	leave  
 772:	c3                   	ret    

00000773 <morecore>:

static Header*
morecore(uint nu)
{
 773:	f3 0f 1e fb          	endbr32 
 777:	55                   	push   %ebp
 778:	89 e5                	mov    %esp,%ebp
 77a:	83 ec 18             	sub    $0x18,%esp
  char *p;
  Header *hp;

  if(nu < 4096)
 77d:	81 7d 08 ff 0f 00 00 	cmpl   $0xfff,0x8(%ebp)
 784:	77 07                	ja     78d <morecore+0x1a>
    nu = 4096;
 786:	c7 45 08 00 10 00 00 	movl   $0x1000,0x8(%ebp)
  p = sbrk(nu * sizeof(Header));
 78d:	8b 45 08             	mov    0x8(%ebp),%eax
 790:	c1 e0 03             	shl    $0x3,%eax
 793:	83 ec 0c             	sub    $0xc,%esp
 796:	50                   	push   %eax
 797:	e8 57 fc ff ff       	call   3f3 <sbrk>
 79c:	83 c4 10             	add    $0x10,%esp
 79f:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(p == (char*)-1)
 7a2:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
 7a6:	75 07                	jne    7af <morecore+0x3c>
    return 0;
 7a8:	b8 00 00 00 00       	mov    $0x0,%eax
 7ad:	eb 26                	jmp    7d5 <morecore+0x62>
  hp = (Header*)p;
 7af:	8b 45 f4             	mov    -0xc(%ebp),%eax
 7b2:	89 45 f0             	mov    %eax,-0x10(%ebp)
  hp->s.size = nu;
 7b5:	8b 45 f0             	mov    -0x10(%ebp),%eax
 7b8:	8b 55 08             	mov    0x8(%ebp),%edx
 7bb:	89 50 04             	mov    %edx,0x4(%eax)
  free((void*)(hp + 1));
 7be:	8b 45 f0             	mov    -0x10(%ebp),%eax
 7c1:	83 c0 08             	add    $0x8,%eax
 7c4:	83 ec 0c             	sub    $0xc,%esp
 7c7:	50                   	push   %eax
 7c8:	e8 c0 fe ff ff       	call   68d <free>
 7cd:	83 c4 10             	add    $0x10,%esp
  return freep;
 7d0:	a1 40 0b 00 00       	mov    0xb40,%eax
}
 7d5:	c9                   	leave  
 7d6:	c3                   	ret    

000007d7 <malloc>:

void*
malloc(uint nbytes)
{
 7d7:	f3 0f 1e fb          	endbr32 
 7db:	55                   	push   %ebp
 7dc:	89 e5                	mov    %esp,%ebp
 7de:	83 ec 18             	sub    $0x18,%esp
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
 7e1:	8b 45 08             	mov    0x8(%ebp),%eax
 7e4:	83 c0 07             	add    $0x7,%eax
 7e7:	c1 e8 03             	shr    $0x3,%eax
 7ea:	83 c0 01             	add    $0x1,%eax
 7ed:	89 45 ec             	mov    %eax,-0x14(%ebp)
  if((prevp = freep) == 0){
 7f0:	a1 40 0b 00 00       	mov    0xb40,%eax
 7f5:	89 45 f0             	mov    %eax,-0x10(%ebp)
 7f8:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 7fc:	75 23                	jne    821 <malloc+0x4a>
    base.s.ptr = freep = prevp = &base;
 7fe:	c7 45 f0 38 0b 00 00 	movl   $0xb38,-0x10(%ebp)
 805:	8b 45 f0             	mov    -0x10(%ebp),%eax
 808:	a3 40 0b 00 00       	mov    %eax,0xb40
 80d:	a1 40 0b 00 00       	mov    0xb40,%eax
 812:	a3 38 0b 00 00       	mov    %eax,0xb38
    base.s.size = 0;
 817:	c7 05 3c 0b 00 00 00 	movl   $0x0,0xb3c
 81e:	00 00 00 
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 821:	8b 45 f0             	mov    -0x10(%ebp),%eax
 824:	8b 00                	mov    (%eax),%eax
 826:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 829:	8b 45 f4             	mov    -0xc(%ebp),%eax
 82c:	8b 40 04             	mov    0x4(%eax),%eax
 82f:	39 45 ec             	cmp    %eax,-0x14(%ebp)
 832:	77 4d                	ja     881 <malloc+0xaa>
      if(p->s.size == nunits)
 834:	8b 45 f4             	mov    -0xc(%ebp),%eax
 837:	8b 40 04             	mov    0x4(%eax),%eax
 83a:	39 45 ec             	cmp    %eax,-0x14(%ebp)
 83d:	75 0c                	jne    84b <malloc+0x74>
        prevp->s.ptr = p->s.ptr;
 83f:	8b 45 f4             	mov    -0xc(%ebp),%eax
 842:	8b 10                	mov    (%eax),%edx
 844:	8b 45 f0             	mov    -0x10(%ebp),%eax
 847:	89 10                	mov    %edx,(%eax)
 849:	eb 26                	jmp    871 <malloc+0x9a>
      else {
        p->s.size -= nunits;
 84b:	8b 45 f4             	mov    -0xc(%ebp),%eax
 84e:	8b 40 04             	mov    0x4(%eax),%eax
 851:	2b 45 ec             	sub    -0x14(%ebp),%eax
 854:	89 c2                	mov    %eax,%edx
 856:	8b 45 f4             	mov    -0xc(%ebp),%eax
 859:	89 50 04             	mov    %edx,0x4(%eax)
        p += p->s.size;
 85c:	8b 45 f4             	mov    -0xc(%ebp),%eax
 85f:	8b 40 04             	mov    0x4(%eax),%eax
 862:	c1 e0 03             	shl    $0x3,%eax
 865:	01 45 f4             	add    %eax,-0xc(%ebp)
        p->s.size = nunits;
 868:	8b 45 f4             	mov    -0xc(%ebp),%eax
 86b:	8b 55 ec             	mov    -0x14(%ebp),%edx
 86e:	89 50 04             	mov    %edx,0x4(%eax)
      }
      freep = prevp;
 871:	8b 45 f0             	mov    -0x10(%ebp),%eax
 874:	a3 40 0b 00 00       	mov    %eax,0xb40
      return (void*)(p + 1);
 879:	8b 45 f4             	mov    -0xc(%ebp),%eax
 87c:	83 c0 08             	add    $0x8,%eax
 87f:	eb 3b                	jmp    8bc <malloc+0xe5>
    }
    if(p == freep)
 881:	a1 40 0b 00 00       	mov    0xb40,%eax
 886:	39 45 f4             	cmp    %eax,-0xc(%ebp)
 889:	75 1e                	jne    8a9 <malloc+0xd2>
      if((p = morecore(nunits)) == 0)
 88b:	83 ec 0c             	sub    $0xc,%esp
 88e:	ff 75 ec             	pushl  -0x14(%ebp)
 891:	e8 dd fe ff ff       	call   773 <morecore>
 896:	83 c4 10             	add    $0x10,%esp
 899:	89 45 f4             	mov    %eax,-0xc(%ebp)
 89c:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 8a0:	75 07                	jne    8a9 <malloc+0xd2>
        return 0;
 8a2:	b8 00 00 00 00       	mov    $0x0,%eax
 8a7:	eb 13                	jmp    8bc <malloc+0xe5>
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 8a9:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8ac:	89 45 f0             	mov    %eax,-0x10(%ebp)
 8af:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8b2:	8b 00                	mov    (%eax),%eax
 8b4:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 8b7:	e9 6d ff ff ff       	jmp    829 <malloc+0x52>
  }
}
 8bc:	c9                   	leave  
 8bd:	c3                   	ret    
