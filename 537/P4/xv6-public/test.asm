
_test:     file format elf32-i386


Disassembly of section .text:

00000000 <main>:
#include "stat.h"
#include "user.h"
#include "psched.h"

int main()
{
   0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
   4:	83 e4 f0             	and    $0xfffffff0,%esp
   7:	ff 71 fc             	push   -0x4(%ecx)
   a:	55                   	push   %ebp
   b:	89 e5                	mov    %esp,%ebp
   d:	51                   	push   %ecx
   e:	81 ec 24 05 00 00    	sub    $0x524,%esp
  struct pschedinfo sch;
  int a = nice(7);
  14:	83 ec 0c             	sub    $0xc,%esp
  17:	6a 07                	push   $0x7
  19:	e8 53 03 00 00       	call   371 <nice>
  1e:	83 c4 10             	add    $0x10,%esp
  21:	89 45 f4             	mov    %eax,-0xc(%ebp)
  int d = sch.priority[0];
  24:	8b 85 e4 fb ff ff    	mov    -0x41c(%ebp),%eax
  2a:	89 45 f0             	mov    %eax,-0x10(%ebp)
  int b = getschedstate(&sch);
  2d:	83 ec 0c             	sub    $0xc,%esp
  30:	8d 85 e4 fa ff ff    	lea    -0x51c(%ebp),%eax
  36:	50                   	push   %eax
  37:	e8 3d 03 00 00       	call   379 <getschedstate>
  3c:	83 c4 10             	add    $0x10,%esp
  3f:	89 45 ec             	mov    %eax,-0x14(%ebp)
  int c = sch.priority[0];
  42:	8b 85 e4 fb ff ff    	mov    -0x41c(%ebp),%eax
  48:	89 45 e8             	mov    %eax,-0x18(%ebp)
  int e = sch.ticks[1];
  4b:	8b 85 e8 fe ff ff    	mov    -0x118(%ebp),%eax
  51:	89 45 e4             	mov    %eax,-0x1c(%ebp)
  printf(1, "%d, %d, %d, %d, !%d!", a, b, c, d, e);
  54:	83 ec 04             	sub    $0x4,%esp
  57:	ff 75 e4             	push   -0x1c(%ebp)
  5a:	ff 75 f0             	push   -0x10(%ebp)
  5d:	ff 75 e8             	push   -0x18(%ebp)
  60:	ff 75 ec             	push   -0x14(%ebp)
  63:	ff 75 f4             	push   -0xc(%ebp)
  66:	68 0c 08 00 00       	push   $0x80c
  6b:	6a 01                	push   $0x1
  6d:	e8 e3 03 00 00       	call   455 <printf>
  72:	83 c4 20             	add    $0x20,%esp
  exit();
  75:	e8 57 02 00 00       	call   2d1 <exit>

0000007a <stosb>:
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{
  7a:	55                   	push   %ebp
  7b:	89 e5                	mov    %esp,%ebp
  7d:	57                   	push   %edi
  7e:	53                   	push   %ebx
  asm volatile("cld; rep stosb" :
  7f:	8b 4d 08             	mov    0x8(%ebp),%ecx
  82:	8b 55 10             	mov    0x10(%ebp),%edx
  85:	8b 45 0c             	mov    0xc(%ebp),%eax
  88:	89 cb                	mov    %ecx,%ebx
  8a:	89 df                	mov    %ebx,%edi
  8c:	89 d1                	mov    %edx,%ecx
  8e:	fc                   	cld    
  8f:	f3 aa                	rep stos %al,%es:(%edi)
  91:	89 ca                	mov    %ecx,%edx
  93:	89 fb                	mov    %edi,%ebx
  95:	89 5d 08             	mov    %ebx,0x8(%ebp)
  98:	89 55 10             	mov    %edx,0x10(%ebp)
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}
  9b:	90                   	nop
  9c:	5b                   	pop    %ebx
  9d:	5f                   	pop    %edi
  9e:	5d                   	pop    %ebp
  9f:	c3                   	ret    

000000a0 <strcpy>:
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
  a0:	55                   	push   %ebp
  a1:	89 e5                	mov    %esp,%ebp
  a3:	83 ec 10             	sub    $0x10,%esp
  char *os;

  os = s;
  a6:	8b 45 08             	mov    0x8(%ebp),%eax
  a9:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while((*s++ = *t++) != 0)
  ac:	90                   	nop
  ad:	8b 55 0c             	mov    0xc(%ebp),%edx
  b0:	8d 42 01             	lea    0x1(%edx),%eax
  b3:	89 45 0c             	mov    %eax,0xc(%ebp)
  b6:	8b 45 08             	mov    0x8(%ebp),%eax
  b9:	8d 48 01             	lea    0x1(%eax),%ecx
  bc:	89 4d 08             	mov    %ecx,0x8(%ebp)
  bf:	0f b6 12             	movzbl (%edx),%edx
  c2:	88 10                	mov    %dl,(%eax)
  c4:	0f b6 00             	movzbl (%eax),%eax
  c7:	84 c0                	test   %al,%al
  c9:	75 e2                	jne    ad <strcpy+0xd>
    ;
  return os;
  cb:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
  ce:	c9                   	leave  
  cf:	c3                   	ret    

000000d0 <strcmp>:

int
strcmp(const char *p, const char *q)
{
  d0:	55                   	push   %ebp
  d1:	89 e5                	mov    %esp,%ebp
  while(*p && *p == *q)
  d3:	eb 08                	jmp    dd <strcmp+0xd>
    p++, q++;
  d5:	83 45 08 01          	addl   $0x1,0x8(%ebp)
  d9:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
  while(*p && *p == *q)
  dd:	8b 45 08             	mov    0x8(%ebp),%eax
  e0:	0f b6 00             	movzbl (%eax),%eax
  e3:	84 c0                	test   %al,%al
  e5:	74 10                	je     f7 <strcmp+0x27>
  e7:	8b 45 08             	mov    0x8(%ebp),%eax
  ea:	0f b6 10             	movzbl (%eax),%edx
  ed:	8b 45 0c             	mov    0xc(%ebp),%eax
  f0:	0f b6 00             	movzbl (%eax),%eax
  f3:	38 c2                	cmp    %al,%dl
  f5:	74 de                	je     d5 <strcmp+0x5>
  return (uchar)*p - (uchar)*q;
  f7:	8b 45 08             	mov    0x8(%ebp),%eax
  fa:	0f b6 00             	movzbl (%eax),%eax
  fd:	0f b6 d0             	movzbl %al,%edx
 100:	8b 45 0c             	mov    0xc(%ebp),%eax
 103:	0f b6 00             	movzbl (%eax),%eax
 106:	0f b6 c8             	movzbl %al,%ecx
 109:	89 d0                	mov    %edx,%eax
 10b:	29 c8                	sub    %ecx,%eax
}
 10d:	5d                   	pop    %ebp
 10e:	c3                   	ret    

0000010f <strlen>:

uint
strlen(const char *s)
{
 10f:	55                   	push   %ebp
 110:	89 e5                	mov    %esp,%ebp
 112:	83 ec 10             	sub    $0x10,%esp
  int n;

  for(n = 0; s[n]; n++)
 115:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
 11c:	eb 04                	jmp    122 <strlen+0x13>
 11e:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 122:	8b 55 fc             	mov    -0x4(%ebp),%edx
 125:	8b 45 08             	mov    0x8(%ebp),%eax
 128:	01 d0                	add    %edx,%eax
 12a:	0f b6 00             	movzbl (%eax),%eax
 12d:	84 c0                	test   %al,%al
 12f:	75 ed                	jne    11e <strlen+0xf>
    ;
  return n;
 131:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 134:	c9                   	leave  
 135:	c3                   	ret    

00000136 <memset>:

void*
memset(void *dst, int c, uint n)
{
 136:	55                   	push   %ebp
 137:	89 e5                	mov    %esp,%ebp
  stosb(dst, c, n);
 139:	8b 45 10             	mov    0x10(%ebp),%eax
 13c:	50                   	push   %eax
 13d:	ff 75 0c             	push   0xc(%ebp)
 140:	ff 75 08             	push   0x8(%ebp)
 143:	e8 32 ff ff ff       	call   7a <stosb>
 148:	83 c4 0c             	add    $0xc,%esp
  return dst;
 14b:	8b 45 08             	mov    0x8(%ebp),%eax
}
 14e:	c9                   	leave  
 14f:	c3                   	ret    

00000150 <strchr>:

char*
strchr(const char *s, char c)
{
 150:	55                   	push   %ebp
 151:	89 e5                	mov    %esp,%ebp
 153:	83 ec 04             	sub    $0x4,%esp
 156:	8b 45 0c             	mov    0xc(%ebp),%eax
 159:	88 45 fc             	mov    %al,-0x4(%ebp)
  for(; *s; s++)
 15c:	eb 14                	jmp    172 <strchr+0x22>
    if(*s == c)
 15e:	8b 45 08             	mov    0x8(%ebp),%eax
 161:	0f b6 00             	movzbl (%eax),%eax
 164:	38 45 fc             	cmp    %al,-0x4(%ebp)
 167:	75 05                	jne    16e <strchr+0x1e>
      return (char*)s;
 169:	8b 45 08             	mov    0x8(%ebp),%eax
 16c:	eb 13                	jmp    181 <strchr+0x31>
  for(; *s; s++)
 16e:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 172:	8b 45 08             	mov    0x8(%ebp),%eax
 175:	0f b6 00             	movzbl (%eax),%eax
 178:	84 c0                	test   %al,%al
 17a:	75 e2                	jne    15e <strchr+0xe>
  return 0;
 17c:	b8 00 00 00 00       	mov    $0x0,%eax
}
 181:	c9                   	leave  
 182:	c3                   	ret    

00000183 <gets>:

char*
gets(char *buf, int max)
{
 183:	55                   	push   %ebp
 184:	89 e5                	mov    %esp,%ebp
 186:	83 ec 18             	sub    $0x18,%esp
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 189:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 190:	eb 42                	jmp    1d4 <gets+0x51>
    cc = read(0, &c, 1);
 192:	83 ec 04             	sub    $0x4,%esp
 195:	6a 01                	push   $0x1
 197:	8d 45 ef             	lea    -0x11(%ebp),%eax
 19a:	50                   	push   %eax
 19b:	6a 00                	push   $0x0
 19d:	e8 47 01 00 00       	call   2e9 <read>
 1a2:	83 c4 10             	add    $0x10,%esp
 1a5:	89 45 f0             	mov    %eax,-0x10(%ebp)
    if(cc < 1)
 1a8:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 1ac:	7e 33                	jle    1e1 <gets+0x5e>
      break;
    buf[i++] = c;
 1ae:	8b 45 f4             	mov    -0xc(%ebp),%eax
 1b1:	8d 50 01             	lea    0x1(%eax),%edx
 1b4:	89 55 f4             	mov    %edx,-0xc(%ebp)
 1b7:	89 c2                	mov    %eax,%edx
 1b9:	8b 45 08             	mov    0x8(%ebp),%eax
 1bc:	01 c2                	add    %eax,%edx
 1be:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 1c2:	88 02                	mov    %al,(%edx)
    if(c == '\n' || c == '\r')
 1c4:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 1c8:	3c 0a                	cmp    $0xa,%al
 1ca:	74 16                	je     1e2 <gets+0x5f>
 1cc:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 1d0:	3c 0d                	cmp    $0xd,%al
 1d2:	74 0e                	je     1e2 <gets+0x5f>
  for(i=0; i+1 < max; ){
 1d4:	8b 45 f4             	mov    -0xc(%ebp),%eax
 1d7:	83 c0 01             	add    $0x1,%eax
 1da:	39 45 0c             	cmp    %eax,0xc(%ebp)
 1dd:	7f b3                	jg     192 <gets+0xf>
 1df:	eb 01                	jmp    1e2 <gets+0x5f>
      break;
 1e1:	90                   	nop
      break;
  }
  buf[i] = '\0';
 1e2:	8b 55 f4             	mov    -0xc(%ebp),%edx
 1e5:	8b 45 08             	mov    0x8(%ebp),%eax
 1e8:	01 d0                	add    %edx,%eax
 1ea:	c6 00 00             	movb   $0x0,(%eax)
  return buf;
 1ed:	8b 45 08             	mov    0x8(%ebp),%eax
}
 1f0:	c9                   	leave  
 1f1:	c3                   	ret    

000001f2 <stat>:

int
stat(const char *n, struct stat *st)
{
 1f2:	55                   	push   %ebp
 1f3:	89 e5                	mov    %esp,%ebp
 1f5:	83 ec 18             	sub    $0x18,%esp
  int fd;
  int r;

  fd = open(n, O_RDONLY);
 1f8:	83 ec 08             	sub    $0x8,%esp
 1fb:	6a 00                	push   $0x0
 1fd:	ff 75 08             	push   0x8(%ebp)
 200:	e8 0c 01 00 00       	call   311 <open>
 205:	83 c4 10             	add    $0x10,%esp
 208:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(fd < 0)
 20b:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 20f:	79 07                	jns    218 <stat+0x26>
    return -1;
 211:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 216:	eb 25                	jmp    23d <stat+0x4b>
  r = fstat(fd, st);
 218:	83 ec 08             	sub    $0x8,%esp
 21b:	ff 75 0c             	push   0xc(%ebp)
 21e:	ff 75 f4             	push   -0xc(%ebp)
 221:	e8 03 01 00 00       	call   329 <fstat>
 226:	83 c4 10             	add    $0x10,%esp
 229:	89 45 f0             	mov    %eax,-0x10(%ebp)
  close(fd);
 22c:	83 ec 0c             	sub    $0xc,%esp
 22f:	ff 75 f4             	push   -0xc(%ebp)
 232:	e8 c2 00 00 00       	call   2f9 <close>
 237:	83 c4 10             	add    $0x10,%esp
  return r;
 23a:	8b 45 f0             	mov    -0x10(%ebp),%eax
}
 23d:	c9                   	leave  
 23e:	c3                   	ret    

0000023f <atoi>:

int
atoi(const char *s)
{
 23f:	55                   	push   %ebp
 240:	89 e5                	mov    %esp,%ebp
 242:	83 ec 10             	sub    $0x10,%esp
  int n;

  n = 0;
 245:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 24c:	eb 25                	jmp    273 <atoi+0x34>
    n = n*10 + *s++ - '0';
 24e:	8b 55 fc             	mov    -0x4(%ebp),%edx
 251:	89 d0                	mov    %edx,%eax
 253:	c1 e0 02             	shl    $0x2,%eax
 256:	01 d0                	add    %edx,%eax
 258:	01 c0                	add    %eax,%eax
 25a:	89 c1                	mov    %eax,%ecx
 25c:	8b 45 08             	mov    0x8(%ebp),%eax
 25f:	8d 50 01             	lea    0x1(%eax),%edx
 262:	89 55 08             	mov    %edx,0x8(%ebp)
 265:	0f b6 00             	movzbl (%eax),%eax
 268:	0f be c0             	movsbl %al,%eax
 26b:	01 c8                	add    %ecx,%eax
 26d:	83 e8 30             	sub    $0x30,%eax
 270:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 273:	8b 45 08             	mov    0x8(%ebp),%eax
 276:	0f b6 00             	movzbl (%eax),%eax
 279:	3c 2f                	cmp    $0x2f,%al
 27b:	7e 0a                	jle    287 <atoi+0x48>
 27d:	8b 45 08             	mov    0x8(%ebp),%eax
 280:	0f b6 00             	movzbl (%eax),%eax
 283:	3c 39                	cmp    $0x39,%al
 285:	7e c7                	jle    24e <atoi+0xf>
  return n;
 287:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 28a:	c9                   	leave  
 28b:	c3                   	ret    

0000028c <memmove>:

void*
memmove(void *vdst, const void *vsrc, int n)
{
 28c:	55                   	push   %ebp
 28d:	89 e5                	mov    %esp,%ebp
 28f:	83 ec 10             	sub    $0x10,%esp
  char *dst;
  const char *src;

  dst = vdst;
 292:	8b 45 08             	mov    0x8(%ebp),%eax
 295:	89 45 fc             	mov    %eax,-0x4(%ebp)
  src = vsrc;
 298:	8b 45 0c             	mov    0xc(%ebp),%eax
 29b:	89 45 f8             	mov    %eax,-0x8(%ebp)
  while(n-- > 0)
 29e:	eb 17                	jmp    2b7 <memmove+0x2b>
    *dst++ = *src++;
 2a0:	8b 55 f8             	mov    -0x8(%ebp),%edx
 2a3:	8d 42 01             	lea    0x1(%edx),%eax
 2a6:	89 45 f8             	mov    %eax,-0x8(%ebp)
 2a9:	8b 45 fc             	mov    -0x4(%ebp),%eax
 2ac:	8d 48 01             	lea    0x1(%eax),%ecx
 2af:	89 4d fc             	mov    %ecx,-0x4(%ebp)
 2b2:	0f b6 12             	movzbl (%edx),%edx
 2b5:	88 10                	mov    %dl,(%eax)
  while(n-- > 0)
 2b7:	8b 45 10             	mov    0x10(%ebp),%eax
 2ba:	8d 50 ff             	lea    -0x1(%eax),%edx
 2bd:	89 55 10             	mov    %edx,0x10(%ebp)
 2c0:	85 c0                	test   %eax,%eax
 2c2:	7f dc                	jg     2a0 <memmove+0x14>
  return vdst;
 2c4:	8b 45 08             	mov    0x8(%ebp),%eax
}
 2c7:	c9                   	leave  
 2c8:	c3                   	ret    

000002c9 <fork>:
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
 2c9:	b8 01 00 00 00       	mov    $0x1,%eax
 2ce:	cd 40                	int    $0x40
 2d0:	c3                   	ret    

000002d1 <exit>:
SYSCALL(exit)
 2d1:	b8 02 00 00 00       	mov    $0x2,%eax
 2d6:	cd 40                	int    $0x40
 2d8:	c3                   	ret    

000002d9 <wait>:
SYSCALL(wait)
 2d9:	b8 03 00 00 00       	mov    $0x3,%eax
 2de:	cd 40                	int    $0x40
 2e0:	c3                   	ret    

000002e1 <pipe>:
SYSCALL(pipe)
 2e1:	b8 04 00 00 00       	mov    $0x4,%eax
 2e6:	cd 40                	int    $0x40
 2e8:	c3                   	ret    

000002e9 <read>:
SYSCALL(read)
 2e9:	b8 05 00 00 00       	mov    $0x5,%eax
 2ee:	cd 40                	int    $0x40
 2f0:	c3                   	ret    

000002f1 <write>:
SYSCALL(write)
 2f1:	b8 10 00 00 00       	mov    $0x10,%eax
 2f6:	cd 40                	int    $0x40
 2f8:	c3                   	ret    

000002f9 <close>:
SYSCALL(close)
 2f9:	b8 15 00 00 00       	mov    $0x15,%eax
 2fe:	cd 40                	int    $0x40
 300:	c3                   	ret    

00000301 <kill>:
SYSCALL(kill)
 301:	b8 06 00 00 00       	mov    $0x6,%eax
 306:	cd 40                	int    $0x40
 308:	c3                   	ret    

00000309 <exec>:
SYSCALL(exec)
 309:	b8 07 00 00 00       	mov    $0x7,%eax
 30e:	cd 40                	int    $0x40
 310:	c3                   	ret    

00000311 <open>:
SYSCALL(open)
 311:	b8 0f 00 00 00       	mov    $0xf,%eax
 316:	cd 40                	int    $0x40
 318:	c3                   	ret    

00000319 <mknod>:
SYSCALL(mknod)
 319:	b8 11 00 00 00       	mov    $0x11,%eax
 31e:	cd 40                	int    $0x40
 320:	c3                   	ret    

00000321 <unlink>:
SYSCALL(unlink)
 321:	b8 12 00 00 00       	mov    $0x12,%eax
 326:	cd 40                	int    $0x40
 328:	c3                   	ret    

00000329 <fstat>:
SYSCALL(fstat)
 329:	b8 08 00 00 00       	mov    $0x8,%eax
 32e:	cd 40                	int    $0x40
 330:	c3                   	ret    

00000331 <link>:
SYSCALL(link)
 331:	b8 13 00 00 00       	mov    $0x13,%eax
 336:	cd 40                	int    $0x40
 338:	c3                   	ret    

00000339 <mkdir>:
SYSCALL(mkdir)
 339:	b8 14 00 00 00       	mov    $0x14,%eax
 33e:	cd 40                	int    $0x40
 340:	c3                   	ret    

00000341 <chdir>:
SYSCALL(chdir)
 341:	b8 09 00 00 00       	mov    $0x9,%eax
 346:	cd 40                	int    $0x40
 348:	c3                   	ret    

00000349 <dup>:
SYSCALL(dup)
 349:	b8 0a 00 00 00       	mov    $0xa,%eax
 34e:	cd 40                	int    $0x40
 350:	c3                   	ret    

00000351 <getpid>:
SYSCALL(getpid)
 351:	b8 0b 00 00 00       	mov    $0xb,%eax
 356:	cd 40                	int    $0x40
 358:	c3                   	ret    

00000359 <sbrk>:
SYSCALL(sbrk)
 359:	b8 0c 00 00 00       	mov    $0xc,%eax
 35e:	cd 40                	int    $0x40
 360:	c3                   	ret    

00000361 <sleep>:
SYSCALL(sleep)
 361:	b8 0d 00 00 00       	mov    $0xd,%eax
 366:	cd 40                	int    $0x40
 368:	c3                   	ret    

00000369 <uptime>:
SYSCALL(uptime)
 369:	b8 0e 00 00 00       	mov    $0xe,%eax
 36e:	cd 40                	int    $0x40
 370:	c3                   	ret    

00000371 <nice>:
SYSCALL(nice)
 371:	b8 16 00 00 00       	mov    $0x16,%eax
 376:	cd 40                	int    $0x40
 378:	c3                   	ret    

00000379 <getschedstate>:
SYSCALL(getschedstate)
 379:	b8 17 00 00 00       	mov    $0x17,%eax
 37e:	cd 40                	int    $0x40
 380:	c3                   	ret    

00000381 <putc>:
#include "stat.h"
#include "user.h"

static void
putc(int fd, char c)
{
 381:	55                   	push   %ebp
 382:	89 e5                	mov    %esp,%ebp
 384:	83 ec 18             	sub    $0x18,%esp
 387:	8b 45 0c             	mov    0xc(%ebp),%eax
 38a:	88 45 f4             	mov    %al,-0xc(%ebp)
  write(fd, &c, 1);
 38d:	83 ec 04             	sub    $0x4,%esp
 390:	6a 01                	push   $0x1
 392:	8d 45 f4             	lea    -0xc(%ebp),%eax
 395:	50                   	push   %eax
 396:	ff 75 08             	push   0x8(%ebp)
 399:	e8 53 ff ff ff       	call   2f1 <write>
 39e:	83 c4 10             	add    $0x10,%esp
}
 3a1:	90                   	nop
 3a2:	c9                   	leave  
 3a3:	c3                   	ret    

000003a4 <printint>:

static void
printint(int fd, int xx, int base, int sgn)
{
 3a4:	55                   	push   %ebp
 3a5:	89 e5                	mov    %esp,%ebp
 3a7:	83 ec 28             	sub    $0x28,%esp
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
 3aa:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  if(sgn && xx < 0){
 3b1:	83 7d 14 00          	cmpl   $0x0,0x14(%ebp)
 3b5:	74 17                	je     3ce <printint+0x2a>
 3b7:	83 7d 0c 00          	cmpl   $0x0,0xc(%ebp)
 3bb:	79 11                	jns    3ce <printint+0x2a>
    neg = 1;
 3bd:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
    x = -xx;
 3c4:	8b 45 0c             	mov    0xc(%ebp),%eax
 3c7:	f7 d8                	neg    %eax
 3c9:	89 45 ec             	mov    %eax,-0x14(%ebp)
 3cc:	eb 06                	jmp    3d4 <printint+0x30>
  } else {
    x = xx;
 3ce:	8b 45 0c             	mov    0xc(%ebp),%eax
 3d1:	89 45 ec             	mov    %eax,-0x14(%ebp)
  }

  i = 0;
 3d4:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  do{
    buf[i++] = digits[x % base];
 3db:	8b 4d 10             	mov    0x10(%ebp),%ecx
 3de:	8b 45 ec             	mov    -0x14(%ebp),%eax
 3e1:	ba 00 00 00 00       	mov    $0x0,%edx
 3e6:	f7 f1                	div    %ecx
 3e8:	89 d1                	mov    %edx,%ecx
 3ea:	8b 45 f4             	mov    -0xc(%ebp),%eax
 3ed:	8d 50 01             	lea    0x1(%eax),%edx
 3f0:	89 55 f4             	mov    %edx,-0xc(%ebp)
 3f3:	0f b6 91 6c 0a 00 00 	movzbl 0xa6c(%ecx),%edx
 3fa:	88 54 05 dc          	mov    %dl,-0x24(%ebp,%eax,1)
  }while((x /= base) != 0);
 3fe:	8b 4d 10             	mov    0x10(%ebp),%ecx
 401:	8b 45 ec             	mov    -0x14(%ebp),%eax
 404:	ba 00 00 00 00       	mov    $0x0,%edx
 409:	f7 f1                	div    %ecx
 40b:	89 45 ec             	mov    %eax,-0x14(%ebp)
 40e:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 412:	75 c7                	jne    3db <printint+0x37>
  if(neg)
 414:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 418:	74 2d                	je     447 <printint+0xa3>
    buf[i++] = '-';
 41a:	8b 45 f4             	mov    -0xc(%ebp),%eax
 41d:	8d 50 01             	lea    0x1(%eax),%edx
 420:	89 55 f4             	mov    %edx,-0xc(%ebp)
 423:	c6 44 05 dc 2d       	movb   $0x2d,-0x24(%ebp,%eax,1)

  while(--i >= 0)
 428:	eb 1d                	jmp    447 <printint+0xa3>
    putc(fd, buf[i]);
 42a:	8d 55 dc             	lea    -0x24(%ebp),%edx
 42d:	8b 45 f4             	mov    -0xc(%ebp),%eax
 430:	01 d0                	add    %edx,%eax
 432:	0f b6 00             	movzbl (%eax),%eax
 435:	0f be c0             	movsbl %al,%eax
 438:	83 ec 08             	sub    $0x8,%esp
 43b:	50                   	push   %eax
 43c:	ff 75 08             	push   0x8(%ebp)
 43f:	e8 3d ff ff ff       	call   381 <putc>
 444:	83 c4 10             	add    $0x10,%esp
  while(--i >= 0)
 447:	83 6d f4 01          	subl   $0x1,-0xc(%ebp)
 44b:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 44f:	79 d9                	jns    42a <printint+0x86>
}
 451:	90                   	nop
 452:	90                   	nop
 453:	c9                   	leave  
 454:	c3                   	ret    

00000455 <printf>:

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, const char *fmt, ...)
{
 455:	55                   	push   %ebp
 456:	89 e5                	mov    %esp,%ebp
 458:	83 ec 28             	sub    $0x28,%esp
  char *s;
  int c, i, state;
  uint *ap;

  state = 0;
 45b:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  ap = (uint*)(void*)&fmt + 1;
 462:	8d 45 0c             	lea    0xc(%ebp),%eax
 465:	83 c0 04             	add    $0x4,%eax
 468:	89 45 e8             	mov    %eax,-0x18(%ebp)
  for(i = 0; fmt[i]; i++){
 46b:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 472:	e9 59 01 00 00       	jmp    5d0 <printf+0x17b>
    c = fmt[i] & 0xff;
 477:	8b 55 0c             	mov    0xc(%ebp),%edx
 47a:	8b 45 f0             	mov    -0x10(%ebp),%eax
 47d:	01 d0                	add    %edx,%eax
 47f:	0f b6 00             	movzbl (%eax),%eax
 482:	0f be c0             	movsbl %al,%eax
 485:	25 ff 00 00 00       	and    $0xff,%eax
 48a:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    if(state == 0){
 48d:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 491:	75 2c                	jne    4bf <printf+0x6a>
      if(c == '%'){
 493:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 497:	75 0c                	jne    4a5 <printf+0x50>
        state = '%';
 499:	c7 45 ec 25 00 00 00 	movl   $0x25,-0x14(%ebp)
 4a0:	e9 27 01 00 00       	jmp    5cc <printf+0x177>
      } else {
        putc(fd, c);
 4a5:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 4a8:	0f be c0             	movsbl %al,%eax
 4ab:	83 ec 08             	sub    $0x8,%esp
 4ae:	50                   	push   %eax
 4af:	ff 75 08             	push   0x8(%ebp)
 4b2:	e8 ca fe ff ff       	call   381 <putc>
 4b7:	83 c4 10             	add    $0x10,%esp
 4ba:	e9 0d 01 00 00       	jmp    5cc <printf+0x177>
      }
    } else if(state == '%'){
 4bf:	83 7d ec 25          	cmpl   $0x25,-0x14(%ebp)
 4c3:	0f 85 03 01 00 00    	jne    5cc <printf+0x177>
      if(c == 'd'){
 4c9:	83 7d e4 64          	cmpl   $0x64,-0x1c(%ebp)
 4cd:	75 1e                	jne    4ed <printf+0x98>
        printint(fd, *ap, 10, 1);
 4cf:	8b 45 e8             	mov    -0x18(%ebp),%eax
 4d2:	8b 00                	mov    (%eax),%eax
 4d4:	6a 01                	push   $0x1
 4d6:	6a 0a                	push   $0xa
 4d8:	50                   	push   %eax
 4d9:	ff 75 08             	push   0x8(%ebp)
 4dc:	e8 c3 fe ff ff       	call   3a4 <printint>
 4e1:	83 c4 10             	add    $0x10,%esp
        ap++;
 4e4:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 4e8:	e9 d8 00 00 00       	jmp    5c5 <printf+0x170>
      } else if(c == 'x' || c == 'p'){
 4ed:	83 7d e4 78          	cmpl   $0x78,-0x1c(%ebp)
 4f1:	74 06                	je     4f9 <printf+0xa4>
 4f3:	83 7d e4 70          	cmpl   $0x70,-0x1c(%ebp)
 4f7:	75 1e                	jne    517 <printf+0xc2>
        printint(fd, *ap, 16, 0);
 4f9:	8b 45 e8             	mov    -0x18(%ebp),%eax
 4fc:	8b 00                	mov    (%eax),%eax
 4fe:	6a 00                	push   $0x0
 500:	6a 10                	push   $0x10
 502:	50                   	push   %eax
 503:	ff 75 08             	push   0x8(%ebp)
 506:	e8 99 fe ff ff       	call   3a4 <printint>
 50b:	83 c4 10             	add    $0x10,%esp
        ap++;
 50e:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 512:	e9 ae 00 00 00       	jmp    5c5 <printf+0x170>
      } else if(c == 's'){
 517:	83 7d e4 73          	cmpl   $0x73,-0x1c(%ebp)
 51b:	75 43                	jne    560 <printf+0x10b>
        s = (char*)*ap;
 51d:	8b 45 e8             	mov    -0x18(%ebp),%eax
 520:	8b 00                	mov    (%eax),%eax
 522:	89 45 f4             	mov    %eax,-0xc(%ebp)
        ap++;
 525:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
        if(s == 0)
 529:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 52d:	75 25                	jne    554 <printf+0xff>
          s = "(null)";
 52f:	c7 45 f4 21 08 00 00 	movl   $0x821,-0xc(%ebp)
        while(*s != 0){
 536:	eb 1c                	jmp    554 <printf+0xff>
          putc(fd, *s);
 538:	8b 45 f4             	mov    -0xc(%ebp),%eax
 53b:	0f b6 00             	movzbl (%eax),%eax
 53e:	0f be c0             	movsbl %al,%eax
 541:	83 ec 08             	sub    $0x8,%esp
 544:	50                   	push   %eax
 545:	ff 75 08             	push   0x8(%ebp)
 548:	e8 34 fe ff ff       	call   381 <putc>
 54d:	83 c4 10             	add    $0x10,%esp
          s++;
 550:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
        while(*s != 0){
 554:	8b 45 f4             	mov    -0xc(%ebp),%eax
 557:	0f b6 00             	movzbl (%eax),%eax
 55a:	84 c0                	test   %al,%al
 55c:	75 da                	jne    538 <printf+0xe3>
 55e:	eb 65                	jmp    5c5 <printf+0x170>
        }
      } else if(c == 'c'){
 560:	83 7d e4 63          	cmpl   $0x63,-0x1c(%ebp)
 564:	75 1d                	jne    583 <printf+0x12e>
        putc(fd, *ap);
 566:	8b 45 e8             	mov    -0x18(%ebp),%eax
 569:	8b 00                	mov    (%eax),%eax
 56b:	0f be c0             	movsbl %al,%eax
 56e:	83 ec 08             	sub    $0x8,%esp
 571:	50                   	push   %eax
 572:	ff 75 08             	push   0x8(%ebp)
 575:	e8 07 fe ff ff       	call   381 <putc>
 57a:	83 c4 10             	add    $0x10,%esp
        ap++;
 57d:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 581:	eb 42                	jmp    5c5 <printf+0x170>
      } else if(c == '%'){
 583:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 587:	75 17                	jne    5a0 <printf+0x14b>
        putc(fd, c);
 589:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 58c:	0f be c0             	movsbl %al,%eax
 58f:	83 ec 08             	sub    $0x8,%esp
 592:	50                   	push   %eax
 593:	ff 75 08             	push   0x8(%ebp)
 596:	e8 e6 fd ff ff       	call   381 <putc>
 59b:	83 c4 10             	add    $0x10,%esp
 59e:	eb 25                	jmp    5c5 <printf+0x170>
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
 5a0:	83 ec 08             	sub    $0x8,%esp
 5a3:	6a 25                	push   $0x25
 5a5:	ff 75 08             	push   0x8(%ebp)
 5a8:	e8 d4 fd ff ff       	call   381 <putc>
 5ad:	83 c4 10             	add    $0x10,%esp
        putc(fd, c);
 5b0:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 5b3:	0f be c0             	movsbl %al,%eax
 5b6:	83 ec 08             	sub    $0x8,%esp
 5b9:	50                   	push   %eax
 5ba:	ff 75 08             	push   0x8(%ebp)
 5bd:	e8 bf fd ff ff       	call   381 <putc>
 5c2:	83 c4 10             	add    $0x10,%esp
      }
      state = 0;
 5c5:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  for(i = 0; fmt[i]; i++){
 5cc:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 5d0:	8b 55 0c             	mov    0xc(%ebp),%edx
 5d3:	8b 45 f0             	mov    -0x10(%ebp),%eax
 5d6:	01 d0                	add    %edx,%eax
 5d8:	0f b6 00             	movzbl (%eax),%eax
 5db:	84 c0                	test   %al,%al
 5dd:	0f 85 94 fe ff ff    	jne    477 <printf+0x22>
    }
  }
}
 5e3:	90                   	nop
 5e4:	90                   	nop
 5e5:	c9                   	leave  
 5e6:	c3                   	ret    

000005e7 <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
 5e7:	55                   	push   %ebp
 5e8:	89 e5                	mov    %esp,%ebp
 5ea:	83 ec 10             	sub    $0x10,%esp
  Header *bp, *p;

  bp = (Header*)ap - 1;
 5ed:	8b 45 08             	mov    0x8(%ebp),%eax
 5f0:	83 e8 08             	sub    $0x8,%eax
 5f3:	89 45 f8             	mov    %eax,-0x8(%ebp)
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 5f6:	a1 88 0a 00 00       	mov    0xa88,%eax
 5fb:	89 45 fc             	mov    %eax,-0x4(%ebp)
 5fe:	eb 24                	jmp    624 <free+0x3d>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
 600:	8b 45 fc             	mov    -0x4(%ebp),%eax
 603:	8b 00                	mov    (%eax),%eax
 605:	39 45 fc             	cmp    %eax,-0x4(%ebp)
 608:	72 12                	jb     61c <free+0x35>
 60a:	8b 45 f8             	mov    -0x8(%ebp),%eax
 60d:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 610:	77 24                	ja     636 <free+0x4f>
 612:	8b 45 fc             	mov    -0x4(%ebp),%eax
 615:	8b 00                	mov    (%eax),%eax
 617:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 61a:	72 1a                	jb     636 <free+0x4f>
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 61c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 61f:	8b 00                	mov    (%eax),%eax
 621:	89 45 fc             	mov    %eax,-0x4(%ebp)
 624:	8b 45 f8             	mov    -0x8(%ebp),%eax
 627:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 62a:	76 d4                	jbe    600 <free+0x19>
 62c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 62f:	8b 00                	mov    (%eax),%eax
 631:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 634:	73 ca                	jae    600 <free+0x19>
      break;
  if(bp + bp->s.size == p->s.ptr){
 636:	8b 45 f8             	mov    -0x8(%ebp),%eax
 639:	8b 40 04             	mov    0x4(%eax),%eax
 63c:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 643:	8b 45 f8             	mov    -0x8(%ebp),%eax
 646:	01 c2                	add    %eax,%edx
 648:	8b 45 fc             	mov    -0x4(%ebp),%eax
 64b:	8b 00                	mov    (%eax),%eax
 64d:	39 c2                	cmp    %eax,%edx
 64f:	75 24                	jne    675 <free+0x8e>
    bp->s.size += p->s.ptr->s.size;
 651:	8b 45 f8             	mov    -0x8(%ebp),%eax
 654:	8b 50 04             	mov    0x4(%eax),%edx
 657:	8b 45 fc             	mov    -0x4(%ebp),%eax
 65a:	8b 00                	mov    (%eax),%eax
 65c:	8b 40 04             	mov    0x4(%eax),%eax
 65f:	01 c2                	add    %eax,%edx
 661:	8b 45 f8             	mov    -0x8(%ebp),%eax
 664:	89 50 04             	mov    %edx,0x4(%eax)
    bp->s.ptr = p->s.ptr->s.ptr;
 667:	8b 45 fc             	mov    -0x4(%ebp),%eax
 66a:	8b 00                	mov    (%eax),%eax
 66c:	8b 10                	mov    (%eax),%edx
 66e:	8b 45 f8             	mov    -0x8(%ebp),%eax
 671:	89 10                	mov    %edx,(%eax)
 673:	eb 0a                	jmp    67f <free+0x98>
  } else
    bp->s.ptr = p->s.ptr;
 675:	8b 45 fc             	mov    -0x4(%ebp),%eax
 678:	8b 10                	mov    (%eax),%edx
 67a:	8b 45 f8             	mov    -0x8(%ebp),%eax
 67d:	89 10                	mov    %edx,(%eax)
  if(p + p->s.size == bp){
 67f:	8b 45 fc             	mov    -0x4(%ebp),%eax
 682:	8b 40 04             	mov    0x4(%eax),%eax
 685:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 68c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 68f:	01 d0                	add    %edx,%eax
 691:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 694:	75 20                	jne    6b6 <free+0xcf>
    p->s.size += bp->s.size;
 696:	8b 45 fc             	mov    -0x4(%ebp),%eax
 699:	8b 50 04             	mov    0x4(%eax),%edx
 69c:	8b 45 f8             	mov    -0x8(%ebp),%eax
 69f:	8b 40 04             	mov    0x4(%eax),%eax
 6a2:	01 c2                	add    %eax,%edx
 6a4:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6a7:	89 50 04             	mov    %edx,0x4(%eax)
    p->s.ptr = bp->s.ptr;
 6aa:	8b 45 f8             	mov    -0x8(%ebp),%eax
 6ad:	8b 10                	mov    (%eax),%edx
 6af:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6b2:	89 10                	mov    %edx,(%eax)
 6b4:	eb 08                	jmp    6be <free+0xd7>
  } else
    p->s.ptr = bp;
 6b6:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6b9:	8b 55 f8             	mov    -0x8(%ebp),%edx
 6bc:	89 10                	mov    %edx,(%eax)
  freep = p;
 6be:	8b 45 fc             	mov    -0x4(%ebp),%eax
 6c1:	a3 88 0a 00 00       	mov    %eax,0xa88
}
 6c6:	90                   	nop
 6c7:	c9                   	leave  
 6c8:	c3                   	ret    

000006c9 <morecore>:

static Header*
morecore(uint nu)
{
 6c9:	55                   	push   %ebp
 6ca:	89 e5                	mov    %esp,%ebp
 6cc:	83 ec 18             	sub    $0x18,%esp
  char *p;
  Header *hp;

  if(nu < 4096)
 6cf:	81 7d 08 ff 0f 00 00 	cmpl   $0xfff,0x8(%ebp)
 6d6:	77 07                	ja     6df <morecore+0x16>
    nu = 4096;
 6d8:	c7 45 08 00 10 00 00 	movl   $0x1000,0x8(%ebp)
  p = sbrk(nu * sizeof(Header));
 6df:	8b 45 08             	mov    0x8(%ebp),%eax
 6e2:	c1 e0 03             	shl    $0x3,%eax
 6e5:	83 ec 0c             	sub    $0xc,%esp
 6e8:	50                   	push   %eax
 6e9:	e8 6b fc ff ff       	call   359 <sbrk>
 6ee:	83 c4 10             	add    $0x10,%esp
 6f1:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(p == (char*)-1)
 6f4:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
 6f8:	75 07                	jne    701 <morecore+0x38>
    return 0;
 6fa:	b8 00 00 00 00       	mov    $0x0,%eax
 6ff:	eb 26                	jmp    727 <morecore+0x5e>
  hp = (Header*)p;
 701:	8b 45 f4             	mov    -0xc(%ebp),%eax
 704:	89 45 f0             	mov    %eax,-0x10(%ebp)
  hp->s.size = nu;
 707:	8b 45 f0             	mov    -0x10(%ebp),%eax
 70a:	8b 55 08             	mov    0x8(%ebp),%edx
 70d:	89 50 04             	mov    %edx,0x4(%eax)
  free((void*)(hp + 1));
 710:	8b 45 f0             	mov    -0x10(%ebp),%eax
 713:	83 c0 08             	add    $0x8,%eax
 716:	83 ec 0c             	sub    $0xc,%esp
 719:	50                   	push   %eax
 71a:	e8 c8 fe ff ff       	call   5e7 <free>
 71f:	83 c4 10             	add    $0x10,%esp
  return freep;
 722:	a1 88 0a 00 00       	mov    0xa88,%eax
}
 727:	c9                   	leave  
 728:	c3                   	ret    

00000729 <malloc>:

void*
malloc(uint nbytes)
{
 729:	55                   	push   %ebp
 72a:	89 e5                	mov    %esp,%ebp
 72c:	83 ec 18             	sub    $0x18,%esp
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
 72f:	8b 45 08             	mov    0x8(%ebp),%eax
 732:	83 c0 07             	add    $0x7,%eax
 735:	c1 e8 03             	shr    $0x3,%eax
 738:	83 c0 01             	add    $0x1,%eax
 73b:	89 45 ec             	mov    %eax,-0x14(%ebp)
  if((prevp = freep) == 0){
 73e:	a1 88 0a 00 00       	mov    0xa88,%eax
 743:	89 45 f0             	mov    %eax,-0x10(%ebp)
 746:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 74a:	75 23                	jne    76f <malloc+0x46>
    base.s.ptr = freep = prevp = &base;
 74c:	c7 45 f0 80 0a 00 00 	movl   $0xa80,-0x10(%ebp)
 753:	8b 45 f0             	mov    -0x10(%ebp),%eax
 756:	a3 88 0a 00 00       	mov    %eax,0xa88
 75b:	a1 88 0a 00 00       	mov    0xa88,%eax
 760:	a3 80 0a 00 00       	mov    %eax,0xa80
    base.s.size = 0;
 765:	c7 05 84 0a 00 00 00 	movl   $0x0,0xa84
 76c:	00 00 00 
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 76f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 772:	8b 00                	mov    (%eax),%eax
 774:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 777:	8b 45 f4             	mov    -0xc(%ebp),%eax
 77a:	8b 40 04             	mov    0x4(%eax),%eax
 77d:	39 45 ec             	cmp    %eax,-0x14(%ebp)
 780:	77 4d                	ja     7cf <malloc+0xa6>
      if(p->s.size == nunits)
 782:	8b 45 f4             	mov    -0xc(%ebp),%eax
 785:	8b 40 04             	mov    0x4(%eax),%eax
 788:	39 45 ec             	cmp    %eax,-0x14(%ebp)
 78b:	75 0c                	jne    799 <malloc+0x70>
        prevp->s.ptr = p->s.ptr;
 78d:	8b 45 f4             	mov    -0xc(%ebp),%eax
 790:	8b 10                	mov    (%eax),%edx
 792:	8b 45 f0             	mov    -0x10(%ebp),%eax
 795:	89 10                	mov    %edx,(%eax)
 797:	eb 26                	jmp    7bf <malloc+0x96>
      else {
        p->s.size -= nunits;
 799:	8b 45 f4             	mov    -0xc(%ebp),%eax
 79c:	8b 40 04             	mov    0x4(%eax),%eax
 79f:	2b 45 ec             	sub    -0x14(%ebp),%eax
 7a2:	89 c2                	mov    %eax,%edx
 7a4:	8b 45 f4             	mov    -0xc(%ebp),%eax
 7a7:	89 50 04             	mov    %edx,0x4(%eax)
        p += p->s.size;
 7aa:	8b 45 f4             	mov    -0xc(%ebp),%eax
 7ad:	8b 40 04             	mov    0x4(%eax),%eax
 7b0:	c1 e0 03             	shl    $0x3,%eax
 7b3:	01 45 f4             	add    %eax,-0xc(%ebp)
        p->s.size = nunits;
 7b6:	8b 45 f4             	mov    -0xc(%ebp),%eax
 7b9:	8b 55 ec             	mov    -0x14(%ebp),%edx
 7bc:	89 50 04             	mov    %edx,0x4(%eax)
      }
      freep = prevp;
 7bf:	8b 45 f0             	mov    -0x10(%ebp),%eax
 7c2:	a3 88 0a 00 00       	mov    %eax,0xa88
      return (void*)(p + 1);
 7c7:	8b 45 f4             	mov    -0xc(%ebp),%eax
 7ca:	83 c0 08             	add    $0x8,%eax
 7cd:	eb 3b                	jmp    80a <malloc+0xe1>
    }
    if(p == freep)
 7cf:	a1 88 0a 00 00       	mov    0xa88,%eax
 7d4:	39 45 f4             	cmp    %eax,-0xc(%ebp)
 7d7:	75 1e                	jne    7f7 <malloc+0xce>
      if((p = morecore(nunits)) == 0)
 7d9:	83 ec 0c             	sub    $0xc,%esp
 7dc:	ff 75 ec             	push   -0x14(%ebp)
 7df:	e8 e5 fe ff ff       	call   6c9 <morecore>
 7e4:	83 c4 10             	add    $0x10,%esp
 7e7:	89 45 f4             	mov    %eax,-0xc(%ebp)
 7ea:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 7ee:	75 07                	jne    7f7 <malloc+0xce>
        return 0;
 7f0:	b8 00 00 00 00       	mov    $0x0,%eax
 7f5:	eb 13                	jmp    80a <malloc+0xe1>
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 7f7:	8b 45 f4             	mov    -0xc(%ebp),%eax
 7fa:	89 45 f0             	mov    %eax,-0x10(%ebp)
 7fd:	8b 45 f4             	mov    -0xc(%ebp),%eax
 800:	8b 00                	mov    (%eax),%eax
 802:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 805:	e9 6d ff ff ff       	jmp    777 <malloc+0x4e>
  }
}
 80a:	c9                   	leave  
 80b:	c3                   	ret    
