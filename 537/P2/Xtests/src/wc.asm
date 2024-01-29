
_wc:     file format elf32-i386


Disassembly of section .text:

00000000 <wc>:

char buf[512];

void
wc(int fd, char *name)
{
   0:	f3 0f 1e fb          	endbr32 
   4:	55                   	push   %ebp
   5:	89 e5                	mov    %esp,%ebp
   7:	83 ec 28             	sub    $0x28,%esp
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
   a:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%ebp)
  11:	8b 45 e8             	mov    -0x18(%ebp),%eax
  14:	89 45 ec             	mov    %eax,-0x14(%ebp)
  17:	8b 45 ec             	mov    -0x14(%ebp),%eax
  1a:	89 45 f0             	mov    %eax,-0x10(%ebp)
  inword = 0;
  1d:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
  while((n = read(fd, buf, sizeof(buf))) > 0){
  24:	eb 69                	jmp    8f <wc+0x8f>
    for(i=0; i<n; i++){
  26:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  2d:	eb 58                	jmp    87 <wc+0x87>
      c++;
  2f:	83 45 e8 01          	addl   $0x1,-0x18(%ebp)
      if(buf[i] == '\n')
  33:	8b 45 f4             	mov    -0xc(%ebp),%eax
  36:	05 80 0c 00 00       	add    $0xc80,%eax
  3b:	0f b6 00             	movzbl (%eax),%eax
  3e:	3c 0a                	cmp    $0xa,%al
  40:	75 04                	jne    46 <wc+0x46>
        l++;
  42:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
      if(strchr(" \r\t\n\v", buf[i]))
  46:	8b 45 f4             	mov    -0xc(%ebp),%eax
  49:	05 80 0c 00 00       	add    $0xc80,%eax
  4e:	0f b6 00             	movzbl (%eax),%eax
  51:	0f be c0             	movsbl %al,%eax
  54:	83 ec 08             	sub    $0x8,%esp
  57:	50                   	push   %eax
  58:	68 93 09 00 00       	push   $0x993
  5d:	e8 49 02 00 00       	call   2ab <strchr>
  62:	83 c4 10             	add    $0x10,%esp
  65:	85 c0                	test   %eax,%eax
  67:	74 09                	je     72 <wc+0x72>
        inword = 0;
  69:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
  70:	eb 11                	jmp    83 <wc+0x83>
      else if(!inword){
  72:	83 7d e4 00          	cmpl   $0x0,-0x1c(%ebp)
  76:	75 0b                	jne    83 <wc+0x83>
        w++;
  78:	83 45 ec 01          	addl   $0x1,-0x14(%ebp)
        inword = 1;
  7c:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%ebp)
    for(i=0; i<n; i++){
  83:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  87:	8b 45 f4             	mov    -0xc(%ebp),%eax
  8a:	3b 45 e0             	cmp    -0x20(%ebp),%eax
  8d:	7c a0                	jl     2f <wc+0x2f>
  while((n = read(fd, buf, sizeof(buf))) > 0){
  8f:	83 ec 04             	sub    $0x4,%esp
  92:	68 00 02 00 00       	push   $0x200
  97:	68 80 0c 00 00       	push   $0xc80
  9c:	ff 75 08             	pushl  0x8(%ebp)
  9f:	e8 b4 03 00 00       	call   458 <read>
  a4:	83 c4 10             	add    $0x10,%esp
  a7:	89 45 e0             	mov    %eax,-0x20(%ebp)
  aa:	83 7d e0 00          	cmpl   $0x0,-0x20(%ebp)
  ae:	0f 8f 72 ff ff ff    	jg     26 <wc+0x26>
      }
    }
  }
  if(n < 0){
  b4:	83 7d e0 00          	cmpl   $0x0,-0x20(%ebp)
  b8:	79 17                	jns    d1 <wc+0xd1>
    printf(1, "wc: read error\n");
  ba:	83 ec 08             	sub    $0x8,%esp
  bd:	68 99 09 00 00       	push   $0x999
  c2:	6a 01                	push   $0x1
  c4:	e8 03 05 00 00       	call   5cc <printf>
  c9:	83 c4 10             	add    $0x10,%esp
    exit();
  cc:	e8 6f 03 00 00       	call   440 <exit>
  }
  printf(1, "%d %d %d %s\n", l, w, c, name);
  d1:	83 ec 08             	sub    $0x8,%esp
  d4:	ff 75 0c             	pushl  0xc(%ebp)
  d7:	ff 75 e8             	pushl  -0x18(%ebp)
  da:	ff 75 ec             	pushl  -0x14(%ebp)
  dd:	ff 75 f0             	pushl  -0x10(%ebp)
  e0:	68 a9 09 00 00       	push   $0x9a9
  e5:	6a 01                	push   $0x1
  e7:	e8 e0 04 00 00       	call   5cc <printf>
  ec:	83 c4 20             	add    $0x20,%esp
}
  ef:	90                   	nop
  f0:	c9                   	leave  
  f1:	c3                   	ret    

000000f2 <main>:

int
main(int argc, char *argv[])
{
  f2:	f3 0f 1e fb          	endbr32 
  f6:	8d 4c 24 04          	lea    0x4(%esp),%ecx
  fa:	83 e4 f0             	and    $0xfffffff0,%esp
  fd:	ff 71 fc             	pushl  -0x4(%ecx)
 100:	55                   	push   %ebp
 101:	89 e5                	mov    %esp,%ebp
 103:	53                   	push   %ebx
 104:	51                   	push   %ecx
 105:	83 ec 10             	sub    $0x10,%esp
 108:	89 cb                	mov    %ecx,%ebx
  int fd, i;

  if(argc <= 1){
 10a:	83 3b 01             	cmpl   $0x1,(%ebx)
 10d:	7f 17                	jg     126 <main+0x34>
    wc(0, "");
 10f:	83 ec 08             	sub    $0x8,%esp
 112:	68 b6 09 00 00       	push   $0x9b6
 117:	6a 00                	push   $0x0
 119:	e8 e2 fe ff ff       	call   0 <wc>
 11e:	83 c4 10             	add    $0x10,%esp
    exit();
 121:	e8 1a 03 00 00       	call   440 <exit>
  }

  for(i = 1; i < argc; i++){
 126:	c7 45 f4 01 00 00 00 	movl   $0x1,-0xc(%ebp)
 12d:	e9 83 00 00 00       	jmp    1b5 <main+0xc3>
    if((fd = open(argv[i], 0)) < 0){
 132:	8b 45 f4             	mov    -0xc(%ebp),%eax
 135:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 13c:	8b 43 04             	mov    0x4(%ebx),%eax
 13f:	01 d0                	add    %edx,%eax
 141:	8b 00                	mov    (%eax),%eax
 143:	83 ec 08             	sub    $0x8,%esp
 146:	6a 00                	push   $0x0
 148:	50                   	push   %eax
 149:	e8 32 03 00 00       	call   480 <open>
 14e:	83 c4 10             	add    $0x10,%esp
 151:	89 45 f0             	mov    %eax,-0x10(%ebp)
 154:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 158:	79 29                	jns    183 <main+0x91>
      printf(1, "wc: cannot open %s\n", argv[i]);
 15a:	8b 45 f4             	mov    -0xc(%ebp),%eax
 15d:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 164:	8b 43 04             	mov    0x4(%ebx),%eax
 167:	01 d0                	add    %edx,%eax
 169:	8b 00                	mov    (%eax),%eax
 16b:	83 ec 04             	sub    $0x4,%esp
 16e:	50                   	push   %eax
 16f:	68 b7 09 00 00       	push   $0x9b7
 174:	6a 01                	push   $0x1
 176:	e8 51 04 00 00       	call   5cc <printf>
 17b:	83 c4 10             	add    $0x10,%esp
      exit();
 17e:	e8 bd 02 00 00       	call   440 <exit>
    }
    wc(fd, argv[i]);
 183:	8b 45 f4             	mov    -0xc(%ebp),%eax
 186:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 18d:	8b 43 04             	mov    0x4(%ebx),%eax
 190:	01 d0                	add    %edx,%eax
 192:	8b 00                	mov    (%eax),%eax
 194:	83 ec 08             	sub    $0x8,%esp
 197:	50                   	push   %eax
 198:	ff 75 f0             	pushl  -0x10(%ebp)
 19b:	e8 60 fe ff ff       	call   0 <wc>
 1a0:	83 c4 10             	add    $0x10,%esp
    close(fd);
 1a3:	83 ec 0c             	sub    $0xc,%esp
 1a6:	ff 75 f0             	pushl  -0x10(%ebp)
 1a9:	e8 ba 02 00 00       	call   468 <close>
 1ae:	83 c4 10             	add    $0x10,%esp
  for(i = 1; i < argc; i++){
 1b1:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 1b5:	8b 45 f4             	mov    -0xc(%ebp),%eax
 1b8:	3b 03                	cmp    (%ebx),%eax
 1ba:	0f 8c 72 ff ff ff    	jl     132 <main+0x40>
  }
  exit();
 1c0:	e8 7b 02 00 00       	call   440 <exit>

000001c5 <stosb>:
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{
 1c5:	55                   	push   %ebp
 1c6:	89 e5                	mov    %esp,%ebp
 1c8:	57                   	push   %edi
 1c9:	53                   	push   %ebx
  asm volatile("cld; rep stosb" :
 1ca:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1cd:	8b 55 10             	mov    0x10(%ebp),%edx
 1d0:	8b 45 0c             	mov    0xc(%ebp),%eax
 1d3:	89 cb                	mov    %ecx,%ebx
 1d5:	89 df                	mov    %ebx,%edi
 1d7:	89 d1                	mov    %edx,%ecx
 1d9:	fc                   	cld    
 1da:	f3 aa                	rep stos %al,%es:(%edi)
 1dc:	89 ca                	mov    %ecx,%edx
 1de:	89 fb                	mov    %edi,%ebx
 1e0:	89 5d 08             	mov    %ebx,0x8(%ebp)
 1e3:	89 55 10             	mov    %edx,0x10(%ebp)
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}
 1e6:	90                   	nop
 1e7:	5b                   	pop    %ebx
 1e8:	5f                   	pop    %edi
 1e9:	5d                   	pop    %ebp
 1ea:	c3                   	ret    

000001eb <strcpy>:
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
 1eb:	f3 0f 1e fb          	endbr32 
 1ef:	55                   	push   %ebp
 1f0:	89 e5                	mov    %esp,%ebp
 1f2:	83 ec 10             	sub    $0x10,%esp
  char *os;

  os = s;
 1f5:	8b 45 08             	mov    0x8(%ebp),%eax
 1f8:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while((*s++ = *t++) != 0)
 1fb:	90                   	nop
 1fc:	8b 55 0c             	mov    0xc(%ebp),%edx
 1ff:	8d 42 01             	lea    0x1(%edx),%eax
 202:	89 45 0c             	mov    %eax,0xc(%ebp)
 205:	8b 45 08             	mov    0x8(%ebp),%eax
 208:	8d 48 01             	lea    0x1(%eax),%ecx
 20b:	89 4d 08             	mov    %ecx,0x8(%ebp)
 20e:	0f b6 12             	movzbl (%edx),%edx
 211:	88 10                	mov    %dl,(%eax)
 213:	0f b6 00             	movzbl (%eax),%eax
 216:	84 c0                	test   %al,%al
 218:	75 e2                	jne    1fc <strcpy+0x11>
    ;
  return os;
 21a:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 21d:	c9                   	leave  
 21e:	c3                   	ret    

0000021f <strcmp>:

int
strcmp(const char *p, const char *q)
{
 21f:	f3 0f 1e fb          	endbr32 
 223:	55                   	push   %ebp
 224:	89 e5                	mov    %esp,%ebp
  while(*p && *p == *q)
 226:	eb 08                	jmp    230 <strcmp+0x11>
    p++, q++;
 228:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 22c:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
  while(*p && *p == *q)
 230:	8b 45 08             	mov    0x8(%ebp),%eax
 233:	0f b6 00             	movzbl (%eax),%eax
 236:	84 c0                	test   %al,%al
 238:	74 10                	je     24a <strcmp+0x2b>
 23a:	8b 45 08             	mov    0x8(%ebp),%eax
 23d:	0f b6 10             	movzbl (%eax),%edx
 240:	8b 45 0c             	mov    0xc(%ebp),%eax
 243:	0f b6 00             	movzbl (%eax),%eax
 246:	38 c2                	cmp    %al,%dl
 248:	74 de                	je     228 <strcmp+0x9>
  return (uchar)*p - (uchar)*q;
 24a:	8b 45 08             	mov    0x8(%ebp),%eax
 24d:	0f b6 00             	movzbl (%eax),%eax
 250:	0f b6 d0             	movzbl %al,%edx
 253:	8b 45 0c             	mov    0xc(%ebp),%eax
 256:	0f b6 00             	movzbl (%eax),%eax
 259:	0f b6 c0             	movzbl %al,%eax
 25c:	29 c2                	sub    %eax,%edx
 25e:	89 d0                	mov    %edx,%eax
}
 260:	5d                   	pop    %ebp
 261:	c3                   	ret    

00000262 <strlen>:

uint
strlen(const char *s)
{
 262:	f3 0f 1e fb          	endbr32 
 266:	55                   	push   %ebp
 267:	89 e5                	mov    %esp,%ebp
 269:	83 ec 10             	sub    $0x10,%esp
  int n;

  for(n = 0; s[n]; n++)
 26c:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
 273:	eb 04                	jmp    279 <strlen+0x17>
 275:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 279:	8b 55 fc             	mov    -0x4(%ebp),%edx
 27c:	8b 45 08             	mov    0x8(%ebp),%eax
 27f:	01 d0                	add    %edx,%eax
 281:	0f b6 00             	movzbl (%eax),%eax
 284:	84 c0                	test   %al,%al
 286:	75 ed                	jne    275 <strlen+0x13>
    ;
  return n;
 288:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 28b:	c9                   	leave  
 28c:	c3                   	ret    

0000028d <memset>:

void*
memset(void *dst, int c, uint n)
{
 28d:	f3 0f 1e fb          	endbr32 
 291:	55                   	push   %ebp
 292:	89 e5                	mov    %esp,%ebp
  stosb(dst, c, n);
 294:	8b 45 10             	mov    0x10(%ebp),%eax
 297:	50                   	push   %eax
 298:	ff 75 0c             	pushl  0xc(%ebp)
 29b:	ff 75 08             	pushl  0x8(%ebp)
 29e:	e8 22 ff ff ff       	call   1c5 <stosb>
 2a3:	83 c4 0c             	add    $0xc,%esp
  return dst;
 2a6:	8b 45 08             	mov    0x8(%ebp),%eax
}
 2a9:	c9                   	leave  
 2aa:	c3                   	ret    

000002ab <strchr>:

char*
strchr(const char *s, char c)
{
 2ab:	f3 0f 1e fb          	endbr32 
 2af:	55                   	push   %ebp
 2b0:	89 e5                	mov    %esp,%ebp
 2b2:	83 ec 04             	sub    $0x4,%esp
 2b5:	8b 45 0c             	mov    0xc(%ebp),%eax
 2b8:	88 45 fc             	mov    %al,-0x4(%ebp)
  for(; *s; s++)
 2bb:	eb 14                	jmp    2d1 <strchr+0x26>
    if(*s == c)
 2bd:	8b 45 08             	mov    0x8(%ebp),%eax
 2c0:	0f b6 00             	movzbl (%eax),%eax
 2c3:	38 45 fc             	cmp    %al,-0x4(%ebp)
 2c6:	75 05                	jne    2cd <strchr+0x22>
      return (char*)s;
 2c8:	8b 45 08             	mov    0x8(%ebp),%eax
 2cb:	eb 13                	jmp    2e0 <strchr+0x35>
  for(; *s; s++)
 2cd:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 2d1:	8b 45 08             	mov    0x8(%ebp),%eax
 2d4:	0f b6 00             	movzbl (%eax),%eax
 2d7:	84 c0                	test   %al,%al
 2d9:	75 e2                	jne    2bd <strchr+0x12>
  return 0;
 2db:	b8 00 00 00 00       	mov    $0x0,%eax
}
 2e0:	c9                   	leave  
 2e1:	c3                   	ret    

000002e2 <gets>:

char*
gets(char *buf, int max)
{
 2e2:	f3 0f 1e fb          	endbr32 
 2e6:	55                   	push   %ebp
 2e7:	89 e5                	mov    %esp,%ebp
 2e9:	83 ec 18             	sub    $0x18,%esp
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 2ec:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 2f3:	eb 42                	jmp    337 <gets+0x55>
    cc = read(0, &c, 1);
 2f5:	83 ec 04             	sub    $0x4,%esp
 2f8:	6a 01                	push   $0x1
 2fa:	8d 45 ef             	lea    -0x11(%ebp),%eax
 2fd:	50                   	push   %eax
 2fe:	6a 00                	push   $0x0
 300:	e8 53 01 00 00       	call   458 <read>
 305:	83 c4 10             	add    $0x10,%esp
 308:	89 45 f0             	mov    %eax,-0x10(%ebp)
    if(cc < 1)
 30b:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 30f:	7e 33                	jle    344 <gets+0x62>
      break;
    buf[i++] = c;
 311:	8b 45 f4             	mov    -0xc(%ebp),%eax
 314:	8d 50 01             	lea    0x1(%eax),%edx
 317:	89 55 f4             	mov    %edx,-0xc(%ebp)
 31a:	89 c2                	mov    %eax,%edx
 31c:	8b 45 08             	mov    0x8(%ebp),%eax
 31f:	01 c2                	add    %eax,%edx
 321:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 325:	88 02                	mov    %al,(%edx)
    if(c == '\n' || c == '\r')
 327:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 32b:	3c 0a                	cmp    $0xa,%al
 32d:	74 16                	je     345 <gets+0x63>
 32f:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 333:	3c 0d                	cmp    $0xd,%al
 335:	74 0e                	je     345 <gets+0x63>
  for(i=0; i+1 < max; ){
 337:	8b 45 f4             	mov    -0xc(%ebp),%eax
 33a:	83 c0 01             	add    $0x1,%eax
 33d:	39 45 0c             	cmp    %eax,0xc(%ebp)
 340:	7f b3                	jg     2f5 <gets+0x13>
 342:	eb 01                	jmp    345 <gets+0x63>
      break;
 344:	90                   	nop
      break;
  }
  buf[i] = '\0';
 345:	8b 55 f4             	mov    -0xc(%ebp),%edx
 348:	8b 45 08             	mov    0x8(%ebp),%eax
 34b:	01 d0                	add    %edx,%eax
 34d:	c6 00 00             	movb   $0x0,(%eax)
  return buf;
 350:	8b 45 08             	mov    0x8(%ebp),%eax
}
 353:	c9                   	leave  
 354:	c3                   	ret    

00000355 <stat>:

int
stat(const char *n, struct stat *st)
{
 355:	f3 0f 1e fb          	endbr32 
 359:	55                   	push   %ebp
 35a:	89 e5                	mov    %esp,%ebp
 35c:	83 ec 18             	sub    $0x18,%esp
  int fd;
  int r;

  fd = open(n, O_RDONLY);
 35f:	83 ec 08             	sub    $0x8,%esp
 362:	6a 00                	push   $0x0
 364:	ff 75 08             	pushl  0x8(%ebp)
 367:	e8 14 01 00 00       	call   480 <open>
 36c:	83 c4 10             	add    $0x10,%esp
 36f:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(fd < 0)
 372:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 376:	79 07                	jns    37f <stat+0x2a>
    return -1;
 378:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 37d:	eb 25                	jmp    3a4 <stat+0x4f>
  r = fstat(fd, st);
 37f:	83 ec 08             	sub    $0x8,%esp
 382:	ff 75 0c             	pushl  0xc(%ebp)
 385:	ff 75 f4             	pushl  -0xc(%ebp)
 388:	e8 0b 01 00 00       	call   498 <fstat>
 38d:	83 c4 10             	add    $0x10,%esp
 390:	89 45 f0             	mov    %eax,-0x10(%ebp)
  close(fd);
 393:	83 ec 0c             	sub    $0xc,%esp
 396:	ff 75 f4             	pushl  -0xc(%ebp)
 399:	e8 ca 00 00 00       	call   468 <close>
 39e:	83 c4 10             	add    $0x10,%esp
  return r;
 3a1:	8b 45 f0             	mov    -0x10(%ebp),%eax
}
 3a4:	c9                   	leave  
 3a5:	c3                   	ret    

000003a6 <atoi>:

int
atoi(const char *s)
{
 3a6:	f3 0f 1e fb          	endbr32 
 3aa:	55                   	push   %ebp
 3ab:	89 e5                	mov    %esp,%ebp
 3ad:	83 ec 10             	sub    $0x10,%esp
  int n;

  n = 0;
 3b0:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 3b7:	eb 25                	jmp    3de <atoi+0x38>
    n = n*10 + *s++ - '0';
 3b9:	8b 55 fc             	mov    -0x4(%ebp),%edx
 3bc:	89 d0                	mov    %edx,%eax
 3be:	c1 e0 02             	shl    $0x2,%eax
 3c1:	01 d0                	add    %edx,%eax
 3c3:	01 c0                	add    %eax,%eax
 3c5:	89 c1                	mov    %eax,%ecx
 3c7:	8b 45 08             	mov    0x8(%ebp),%eax
 3ca:	8d 50 01             	lea    0x1(%eax),%edx
 3cd:	89 55 08             	mov    %edx,0x8(%ebp)
 3d0:	0f b6 00             	movzbl (%eax),%eax
 3d3:	0f be c0             	movsbl %al,%eax
 3d6:	01 c8                	add    %ecx,%eax
 3d8:	83 e8 30             	sub    $0x30,%eax
 3db:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 3de:	8b 45 08             	mov    0x8(%ebp),%eax
 3e1:	0f b6 00             	movzbl (%eax),%eax
 3e4:	3c 2f                	cmp    $0x2f,%al
 3e6:	7e 0a                	jle    3f2 <atoi+0x4c>
 3e8:	8b 45 08             	mov    0x8(%ebp),%eax
 3eb:	0f b6 00             	movzbl (%eax),%eax
 3ee:	3c 39                	cmp    $0x39,%al
 3f0:	7e c7                	jle    3b9 <atoi+0x13>
  return n;
 3f2:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 3f5:	c9                   	leave  
 3f6:	c3                   	ret    

000003f7 <memmove>:

void*
memmove(void *vdst, const void *vsrc, int n)
{
 3f7:	f3 0f 1e fb          	endbr32 
 3fb:	55                   	push   %ebp
 3fc:	89 e5                	mov    %esp,%ebp
 3fe:	83 ec 10             	sub    $0x10,%esp
  char *dst;
  const char *src;

  dst = vdst;
 401:	8b 45 08             	mov    0x8(%ebp),%eax
 404:	89 45 fc             	mov    %eax,-0x4(%ebp)
  src = vsrc;
 407:	8b 45 0c             	mov    0xc(%ebp),%eax
 40a:	89 45 f8             	mov    %eax,-0x8(%ebp)
  while(n-- > 0)
 40d:	eb 17                	jmp    426 <memmove+0x2f>
    *dst++ = *src++;
 40f:	8b 55 f8             	mov    -0x8(%ebp),%edx
 412:	8d 42 01             	lea    0x1(%edx),%eax
 415:	89 45 f8             	mov    %eax,-0x8(%ebp)
 418:	8b 45 fc             	mov    -0x4(%ebp),%eax
 41b:	8d 48 01             	lea    0x1(%eax),%ecx
 41e:	89 4d fc             	mov    %ecx,-0x4(%ebp)
 421:	0f b6 12             	movzbl (%edx),%edx
 424:	88 10                	mov    %dl,(%eax)
  while(n-- > 0)
 426:	8b 45 10             	mov    0x10(%ebp),%eax
 429:	8d 50 ff             	lea    -0x1(%eax),%edx
 42c:	89 55 10             	mov    %edx,0x10(%ebp)
 42f:	85 c0                	test   %eax,%eax
 431:	7f dc                	jg     40f <memmove+0x18>
  return vdst;
 433:	8b 45 08             	mov    0x8(%ebp),%eax
}
 436:	c9                   	leave  
 437:	c3                   	ret    

00000438 <fork>:
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
 438:	b8 01 00 00 00       	mov    $0x1,%eax
 43d:	cd 40                	int    $0x40
 43f:	c3                   	ret    

00000440 <exit>:
SYSCALL(exit)
 440:	b8 02 00 00 00       	mov    $0x2,%eax
 445:	cd 40                	int    $0x40
 447:	c3                   	ret    

00000448 <wait>:
SYSCALL(wait)
 448:	b8 03 00 00 00       	mov    $0x3,%eax
 44d:	cd 40                	int    $0x40
 44f:	c3                   	ret    

00000450 <pipe>:
SYSCALL(pipe)
 450:	b8 04 00 00 00       	mov    $0x4,%eax
 455:	cd 40                	int    $0x40
 457:	c3                   	ret    

00000458 <read>:
SYSCALL(read)
 458:	b8 05 00 00 00       	mov    $0x5,%eax
 45d:	cd 40                	int    $0x40
 45f:	c3                   	ret    

00000460 <write>:
SYSCALL(write)
 460:	b8 10 00 00 00       	mov    $0x10,%eax
 465:	cd 40                	int    $0x40
 467:	c3                   	ret    

00000468 <close>:
SYSCALL(close)
 468:	b8 15 00 00 00       	mov    $0x15,%eax
 46d:	cd 40                	int    $0x40
 46f:	c3                   	ret    

00000470 <kill>:
SYSCALL(kill)
 470:	b8 06 00 00 00       	mov    $0x6,%eax
 475:	cd 40                	int    $0x40
 477:	c3                   	ret    

00000478 <exec>:
SYSCALL(exec)
 478:	b8 07 00 00 00       	mov    $0x7,%eax
 47d:	cd 40                	int    $0x40
 47f:	c3                   	ret    

00000480 <open>:
SYSCALL(open)
 480:	b8 0f 00 00 00       	mov    $0xf,%eax
 485:	cd 40                	int    $0x40
 487:	c3                   	ret    

00000488 <mknod>:
SYSCALL(mknod)
 488:	b8 11 00 00 00       	mov    $0x11,%eax
 48d:	cd 40                	int    $0x40
 48f:	c3                   	ret    

00000490 <unlink>:
SYSCALL(unlink)
 490:	b8 12 00 00 00       	mov    $0x12,%eax
 495:	cd 40                	int    $0x40
 497:	c3                   	ret    

00000498 <fstat>:
SYSCALL(fstat)
 498:	b8 08 00 00 00       	mov    $0x8,%eax
 49d:	cd 40                	int    $0x40
 49f:	c3                   	ret    

000004a0 <link>:
SYSCALL(link)
 4a0:	b8 13 00 00 00       	mov    $0x13,%eax
 4a5:	cd 40                	int    $0x40
 4a7:	c3                   	ret    

000004a8 <mkdir>:
SYSCALL(mkdir)
 4a8:	b8 14 00 00 00       	mov    $0x14,%eax
 4ad:	cd 40                	int    $0x40
 4af:	c3                   	ret    

000004b0 <chdir>:
SYSCALL(chdir)
 4b0:	b8 09 00 00 00       	mov    $0x9,%eax
 4b5:	cd 40                	int    $0x40
 4b7:	c3                   	ret    

000004b8 <dup>:
SYSCALL(dup)
 4b8:	b8 0a 00 00 00       	mov    $0xa,%eax
 4bd:	cd 40                	int    $0x40
 4bf:	c3                   	ret    

000004c0 <getpid>:
SYSCALL(getpid)
 4c0:	b8 0b 00 00 00       	mov    $0xb,%eax
 4c5:	cd 40                	int    $0x40
 4c7:	c3                   	ret    

000004c8 <sbrk>:
SYSCALL(sbrk)
 4c8:	b8 0c 00 00 00       	mov    $0xc,%eax
 4cd:	cd 40                	int    $0x40
 4cf:	c3                   	ret    

000004d0 <sleep>:
SYSCALL(sleep)
 4d0:	b8 0d 00 00 00       	mov    $0xd,%eax
 4d5:	cd 40                	int    $0x40
 4d7:	c3                   	ret    

000004d8 <uptime>:
SYSCALL(uptime)
 4d8:	b8 0e 00 00 00       	mov    $0xe,%eax
 4dd:	cd 40                	int    $0x40
 4df:	c3                   	ret    

000004e0 <getnumsyscalls>:
SYSCALL(getnumsyscalls)
 4e0:	b8 16 00 00 00       	mov    $0x16,%eax
 4e5:	cd 40                	int    $0x40
 4e7:	c3                   	ret    

000004e8 <getnumsyscallsgood>:
SYSCALL(getnumsyscallsgood)
 4e8:	b8 17 00 00 00       	mov    $0x17,%eax
 4ed:	cd 40                	int    $0x40
 4ef:	c3                   	ret    

000004f0 <putc>:
#include "stat.h"
#include "user.h"

static void
putc(int fd, char c)
{
 4f0:	f3 0f 1e fb          	endbr32 
 4f4:	55                   	push   %ebp
 4f5:	89 e5                	mov    %esp,%ebp
 4f7:	83 ec 18             	sub    $0x18,%esp
 4fa:	8b 45 0c             	mov    0xc(%ebp),%eax
 4fd:	88 45 f4             	mov    %al,-0xc(%ebp)
  write(fd, &c, 1);
 500:	83 ec 04             	sub    $0x4,%esp
 503:	6a 01                	push   $0x1
 505:	8d 45 f4             	lea    -0xc(%ebp),%eax
 508:	50                   	push   %eax
 509:	ff 75 08             	pushl  0x8(%ebp)
 50c:	e8 4f ff ff ff       	call   460 <write>
 511:	83 c4 10             	add    $0x10,%esp
}
 514:	90                   	nop
 515:	c9                   	leave  
 516:	c3                   	ret    

00000517 <printint>:

static void
printint(int fd, int xx, int base, int sgn)
{
 517:	f3 0f 1e fb          	endbr32 
 51b:	55                   	push   %ebp
 51c:	89 e5                	mov    %esp,%ebp
 51e:	83 ec 28             	sub    $0x28,%esp
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
 521:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  if(sgn && xx < 0){
 528:	83 7d 14 00          	cmpl   $0x0,0x14(%ebp)
 52c:	74 17                	je     545 <printint+0x2e>
 52e:	83 7d 0c 00          	cmpl   $0x0,0xc(%ebp)
 532:	79 11                	jns    545 <printint+0x2e>
    neg = 1;
 534:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
    x = -xx;
 53b:	8b 45 0c             	mov    0xc(%ebp),%eax
 53e:	f7 d8                	neg    %eax
 540:	89 45 ec             	mov    %eax,-0x14(%ebp)
 543:	eb 06                	jmp    54b <printint+0x34>
  } else {
    x = xx;
 545:	8b 45 0c             	mov    0xc(%ebp),%eax
 548:	89 45 ec             	mov    %eax,-0x14(%ebp)
  }

  i = 0;
 54b:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  do{
    buf[i++] = digits[x % base];
 552:	8b 4d 10             	mov    0x10(%ebp),%ecx
 555:	8b 45 ec             	mov    -0x14(%ebp),%eax
 558:	ba 00 00 00 00       	mov    $0x0,%edx
 55d:	f7 f1                	div    %ecx
 55f:	89 d1                	mov    %edx,%ecx
 561:	8b 45 f4             	mov    -0xc(%ebp),%eax
 564:	8d 50 01             	lea    0x1(%eax),%edx
 567:	89 55 f4             	mov    %edx,-0xc(%ebp)
 56a:	0f b6 91 3c 0c 00 00 	movzbl 0xc3c(%ecx),%edx
 571:	88 54 05 dc          	mov    %dl,-0x24(%ebp,%eax,1)
  }while((x /= base) != 0);
 575:	8b 4d 10             	mov    0x10(%ebp),%ecx
 578:	8b 45 ec             	mov    -0x14(%ebp),%eax
 57b:	ba 00 00 00 00       	mov    $0x0,%edx
 580:	f7 f1                	div    %ecx
 582:	89 45 ec             	mov    %eax,-0x14(%ebp)
 585:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 589:	75 c7                	jne    552 <printint+0x3b>
  if(neg)
 58b:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 58f:	74 2d                	je     5be <printint+0xa7>
    buf[i++] = '-';
 591:	8b 45 f4             	mov    -0xc(%ebp),%eax
 594:	8d 50 01             	lea    0x1(%eax),%edx
 597:	89 55 f4             	mov    %edx,-0xc(%ebp)
 59a:	c6 44 05 dc 2d       	movb   $0x2d,-0x24(%ebp,%eax,1)

  while(--i >= 0)
 59f:	eb 1d                	jmp    5be <printint+0xa7>
    putc(fd, buf[i]);
 5a1:	8d 55 dc             	lea    -0x24(%ebp),%edx
 5a4:	8b 45 f4             	mov    -0xc(%ebp),%eax
 5a7:	01 d0                	add    %edx,%eax
 5a9:	0f b6 00             	movzbl (%eax),%eax
 5ac:	0f be c0             	movsbl %al,%eax
 5af:	83 ec 08             	sub    $0x8,%esp
 5b2:	50                   	push   %eax
 5b3:	ff 75 08             	pushl  0x8(%ebp)
 5b6:	e8 35 ff ff ff       	call   4f0 <putc>
 5bb:	83 c4 10             	add    $0x10,%esp
  while(--i >= 0)
 5be:	83 6d f4 01          	subl   $0x1,-0xc(%ebp)
 5c2:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 5c6:	79 d9                	jns    5a1 <printint+0x8a>
}
 5c8:	90                   	nop
 5c9:	90                   	nop
 5ca:	c9                   	leave  
 5cb:	c3                   	ret    

000005cc <printf>:

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, const char *fmt, ...)
{
 5cc:	f3 0f 1e fb          	endbr32 
 5d0:	55                   	push   %ebp
 5d1:	89 e5                	mov    %esp,%ebp
 5d3:	83 ec 28             	sub    $0x28,%esp
  char *s;
  int c, i, state;
  uint *ap;

  state = 0;
 5d6:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  ap = (uint*)(void*)&fmt + 1;
 5dd:	8d 45 0c             	lea    0xc(%ebp),%eax
 5e0:	83 c0 04             	add    $0x4,%eax
 5e3:	89 45 e8             	mov    %eax,-0x18(%ebp)
  for(i = 0; fmt[i]; i++){
 5e6:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 5ed:	e9 59 01 00 00       	jmp    74b <printf+0x17f>
    c = fmt[i] & 0xff;
 5f2:	8b 55 0c             	mov    0xc(%ebp),%edx
 5f5:	8b 45 f0             	mov    -0x10(%ebp),%eax
 5f8:	01 d0                	add    %edx,%eax
 5fa:	0f b6 00             	movzbl (%eax),%eax
 5fd:	0f be c0             	movsbl %al,%eax
 600:	25 ff 00 00 00       	and    $0xff,%eax
 605:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    if(state == 0){
 608:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 60c:	75 2c                	jne    63a <printf+0x6e>
      if(c == '%'){
 60e:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 612:	75 0c                	jne    620 <printf+0x54>
        state = '%';
 614:	c7 45 ec 25 00 00 00 	movl   $0x25,-0x14(%ebp)
 61b:	e9 27 01 00 00       	jmp    747 <printf+0x17b>
      } else {
        putc(fd, c);
 620:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 623:	0f be c0             	movsbl %al,%eax
 626:	83 ec 08             	sub    $0x8,%esp
 629:	50                   	push   %eax
 62a:	ff 75 08             	pushl  0x8(%ebp)
 62d:	e8 be fe ff ff       	call   4f0 <putc>
 632:	83 c4 10             	add    $0x10,%esp
 635:	e9 0d 01 00 00       	jmp    747 <printf+0x17b>
      }
    } else if(state == '%'){
 63a:	83 7d ec 25          	cmpl   $0x25,-0x14(%ebp)
 63e:	0f 85 03 01 00 00    	jne    747 <printf+0x17b>
      if(c == 'd'){
 644:	83 7d e4 64          	cmpl   $0x64,-0x1c(%ebp)
 648:	75 1e                	jne    668 <printf+0x9c>
        printint(fd, *ap, 10, 1);
 64a:	8b 45 e8             	mov    -0x18(%ebp),%eax
 64d:	8b 00                	mov    (%eax),%eax
 64f:	6a 01                	push   $0x1
 651:	6a 0a                	push   $0xa
 653:	50                   	push   %eax
 654:	ff 75 08             	pushl  0x8(%ebp)
 657:	e8 bb fe ff ff       	call   517 <printint>
 65c:	83 c4 10             	add    $0x10,%esp
        ap++;
 65f:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 663:	e9 d8 00 00 00       	jmp    740 <printf+0x174>
      } else if(c == 'x' || c == 'p'){
 668:	83 7d e4 78          	cmpl   $0x78,-0x1c(%ebp)
 66c:	74 06                	je     674 <printf+0xa8>
 66e:	83 7d e4 70          	cmpl   $0x70,-0x1c(%ebp)
 672:	75 1e                	jne    692 <printf+0xc6>
        printint(fd, *ap, 16, 0);
 674:	8b 45 e8             	mov    -0x18(%ebp),%eax
 677:	8b 00                	mov    (%eax),%eax
 679:	6a 00                	push   $0x0
 67b:	6a 10                	push   $0x10
 67d:	50                   	push   %eax
 67e:	ff 75 08             	pushl  0x8(%ebp)
 681:	e8 91 fe ff ff       	call   517 <printint>
 686:	83 c4 10             	add    $0x10,%esp
        ap++;
 689:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 68d:	e9 ae 00 00 00       	jmp    740 <printf+0x174>
      } else if(c == 's'){
 692:	83 7d e4 73          	cmpl   $0x73,-0x1c(%ebp)
 696:	75 43                	jne    6db <printf+0x10f>
        s = (char*)*ap;
 698:	8b 45 e8             	mov    -0x18(%ebp),%eax
 69b:	8b 00                	mov    (%eax),%eax
 69d:	89 45 f4             	mov    %eax,-0xc(%ebp)
        ap++;
 6a0:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
        if(s == 0)
 6a4:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 6a8:	75 25                	jne    6cf <printf+0x103>
          s = "(null)";
 6aa:	c7 45 f4 cb 09 00 00 	movl   $0x9cb,-0xc(%ebp)
        while(*s != 0){
 6b1:	eb 1c                	jmp    6cf <printf+0x103>
          putc(fd, *s);
 6b3:	8b 45 f4             	mov    -0xc(%ebp),%eax
 6b6:	0f b6 00             	movzbl (%eax),%eax
 6b9:	0f be c0             	movsbl %al,%eax
 6bc:	83 ec 08             	sub    $0x8,%esp
 6bf:	50                   	push   %eax
 6c0:	ff 75 08             	pushl  0x8(%ebp)
 6c3:	e8 28 fe ff ff       	call   4f0 <putc>
 6c8:	83 c4 10             	add    $0x10,%esp
          s++;
 6cb:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
        while(*s != 0){
 6cf:	8b 45 f4             	mov    -0xc(%ebp),%eax
 6d2:	0f b6 00             	movzbl (%eax),%eax
 6d5:	84 c0                	test   %al,%al
 6d7:	75 da                	jne    6b3 <printf+0xe7>
 6d9:	eb 65                	jmp    740 <printf+0x174>
        }
      } else if(c == 'c'){
 6db:	83 7d e4 63          	cmpl   $0x63,-0x1c(%ebp)
 6df:	75 1d                	jne    6fe <printf+0x132>
        putc(fd, *ap);
 6e1:	8b 45 e8             	mov    -0x18(%ebp),%eax
 6e4:	8b 00                	mov    (%eax),%eax
 6e6:	0f be c0             	movsbl %al,%eax
 6e9:	83 ec 08             	sub    $0x8,%esp
 6ec:	50                   	push   %eax
 6ed:	ff 75 08             	pushl  0x8(%ebp)
 6f0:	e8 fb fd ff ff       	call   4f0 <putc>
 6f5:	83 c4 10             	add    $0x10,%esp
        ap++;
 6f8:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 6fc:	eb 42                	jmp    740 <printf+0x174>
      } else if(c == '%'){
 6fe:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 702:	75 17                	jne    71b <printf+0x14f>
        putc(fd, c);
 704:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 707:	0f be c0             	movsbl %al,%eax
 70a:	83 ec 08             	sub    $0x8,%esp
 70d:	50                   	push   %eax
 70e:	ff 75 08             	pushl  0x8(%ebp)
 711:	e8 da fd ff ff       	call   4f0 <putc>
 716:	83 c4 10             	add    $0x10,%esp
 719:	eb 25                	jmp    740 <printf+0x174>
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
 71b:	83 ec 08             	sub    $0x8,%esp
 71e:	6a 25                	push   $0x25
 720:	ff 75 08             	pushl  0x8(%ebp)
 723:	e8 c8 fd ff ff       	call   4f0 <putc>
 728:	83 c4 10             	add    $0x10,%esp
        putc(fd, c);
 72b:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 72e:	0f be c0             	movsbl %al,%eax
 731:	83 ec 08             	sub    $0x8,%esp
 734:	50                   	push   %eax
 735:	ff 75 08             	pushl  0x8(%ebp)
 738:	e8 b3 fd ff ff       	call   4f0 <putc>
 73d:	83 c4 10             	add    $0x10,%esp
      }
      state = 0;
 740:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  for(i = 0; fmt[i]; i++){
 747:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 74b:	8b 55 0c             	mov    0xc(%ebp),%edx
 74e:	8b 45 f0             	mov    -0x10(%ebp),%eax
 751:	01 d0                	add    %edx,%eax
 753:	0f b6 00             	movzbl (%eax),%eax
 756:	84 c0                	test   %al,%al
 758:	0f 85 94 fe ff ff    	jne    5f2 <printf+0x26>
    }
  }
}
 75e:	90                   	nop
 75f:	90                   	nop
 760:	c9                   	leave  
 761:	c3                   	ret    

00000762 <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
 762:	f3 0f 1e fb          	endbr32 
 766:	55                   	push   %ebp
 767:	89 e5                	mov    %esp,%ebp
 769:	83 ec 10             	sub    $0x10,%esp
  Header *bp, *p;

  bp = (Header*)ap - 1;
 76c:	8b 45 08             	mov    0x8(%ebp),%eax
 76f:	83 e8 08             	sub    $0x8,%eax
 772:	89 45 f8             	mov    %eax,-0x8(%ebp)
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 775:	a1 68 0c 00 00       	mov    0xc68,%eax
 77a:	89 45 fc             	mov    %eax,-0x4(%ebp)
 77d:	eb 24                	jmp    7a3 <free+0x41>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
 77f:	8b 45 fc             	mov    -0x4(%ebp),%eax
 782:	8b 00                	mov    (%eax),%eax
 784:	39 45 fc             	cmp    %eax,-0x4(%ebp)
 787:	72 12                	jb     79b <free+0x39>
 789:	8b 45 f8             	mov    -0x8(%ebp),%eax
 78c:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 78f:	77 24                	ja     7b5 <free+0x53>
 791:	8b 45 fc             	mov    -0x4(%ebp),%eax
 794:	8b 00                	mov    (%eax),%eax
 796:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 799:	72 1a                	jb     7b5 <free+0x53>
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 79b:	8b 45 fc             	mov    -0x4(%ebp),%eax
 79e:	8b 00                	mov    (%eax),%eax
 7a0:	89 45 fc             	mov    %eax,-0x4(%ebp)
 7a3:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7a6:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 7a9:	76 d4                	jbe    77f <free+0x1d>
 7ab:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7ae:	8b 00                	mov    (%eax),%eax
 7b0:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 7b3:	73 ca                	jae    77f <free+0x1d>
      break;
  if(bp + bp->s.size == p->s.ptr){
 7b5:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7b8:	8b 40 04             	mov    0x4(%eax),%eax
 7bb:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 7c2:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7c5:	01 c2                	add    %eax,%edx
 7c7:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7ca:	8b 00                	mov    (%eax),%eax
 7cc:	39 c2                	cmp    %eax,%edx
 7ce:	75 24                	jne    7f4 <free+0x92>
    bp->s.size += p->s.ptr->s.size;
 7d0:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7d3:	8b 50 04             	mov    0x4(%eax),%edx
 7d6:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7d9:	8b 00                	mov    (%eax),%eax
 7db:	8b 40 04             	mov    0x4(%eax),%eax
 7de:	01 c2                	add    %eax,%edx
 7e0:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7e3:	89 50 04             	mov    %edx,0x4(%eax)
    bp->s.ptr = p->s.ptr->s.ptr;
 7e6:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7e9:	8b 00                	mov    (%eax),%eax
 7eb:	8b 10                	mov    (%eax),%edx
 7ed:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7f0:	89 10                	mov    %edx,(%eax)
 7f2:	eb 0a                	jmp    7fe <free+0x9c>
  } else
    bp->s.ptr = p->s.ptr;
 7f4:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7f7:	8b 10                	mov    (%eax),%edx
 7f9:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7fc:	89 10                	mov    %edx,(%eax)
  if(p + p->s.size == bp){
 7fe:	8b 45 fc             	mov    -0x4(%ebp),%eax
 801:	8b 40 04             	mov    0x4(%eax),%eax
 804:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 80b:	8b 45 fc             	mov    -0x4(%ebp),%eax
 80e:	01 d0                	add    %edx,%eax
 810:	39 45 f8             	cmp    %eax,-0x8(%ebp)
 813:	75 20                	jne    835 <free+0xd3>
    p->s.size += bp->s.size;
 815:	8b 45 fc             	mov    -0x4(%ebp),%eax
 818:	8b 50 04             	mov    0x4(%eax),%edx
 81b:	8b 45 f8             	mov    -0x8(%ebp),%eax
 81e:	8b 40 04             	mov    0x4(%eax),%eax
 821:	01 c2                	add    %eax,%edx
 823:	8b 45 fc             	mov    -0x4(%ebp),%eax
 826:	89 50 04             	mov    %edx,0x4(%eax)
    p->s.ptr = bp->s.ptr;
 829:	8b 45 f8             	mov    -0x8(%ebp),%eax
 82c:	8b 10                	mov    (%eax),%edx
 82e:	8b 45 fc             	mov    -0x4(%ebp),%eax
 831:	89 10                	mov    %edx,(%eax)
 833:	eb 08                	jmp    83d <free+0xdb>
  } else
    p->s.ptr = bp;
 835:	8b 45 fc             	mov    -0x4(%ebp),%eax
 838:	8b 55 f8             	mov    -0x8(%ebp),%edx
 83b:	89 10                	mov    %edx,(%eax)
  freep = p;
 83d:	8b 45 fc             	mov    -0x4(%ebp),%eax
 840:	a3 68 0c 00 00       	mov    %eax,0xc68
}
 845:	90                   	nop
 846:	c9                   	leave  
 847:	c3                   	ret    

00000848 <morecore>:

static Header*
morecore(uint nu)
{
 848:	f3 0f 1e fb          	endbr32 
 84c:	55                   	push   %ebp
 84d:	89 e5                	mov    %esp,%ebp
 84f:	83 ec 18             	sub    $0x18,%esp
  char *p;
  Header *hp;

  if(nu < 4096)
 852:	81 7d 08 ff 0f 00 00 	cmpl   $0xfff,0x8(%ebp)
 859:	77 07                	ja     862 <morecore+0x1a>
    nu = 4096;
 85b:	c7 45 08 00 10 00 00 	movl   $0x1000,0x8(%ebp)
  p = sbrk(nu * sizeof(Header));
 862:	8b 45 08             	mov    0x8(%ebp),%eax
 865:	c1 e0 03             	shl    $0x3,%eax
 868:	83 ec 0c             	sub    $0xc,%esp
 86b:	50                   	push   %eax
 86c:	e8 57 fc ff ff       	call   4c8 <sbrk>
 871:	83 c4 10             	add    $0x10,%esp
 874:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(p == (char*)-1)
 877:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
 87b:	75 07                	jne    884 <morecore+0x3c>
    return 0;
 87d:	b8 00 00 00 00       	mov    $0x0,%eax
 882:	eb 26                	jmp    8aa <morecore+0x62>
  hp = (Header*)p;
 884:	8b 45 f4             	mov    -0xc(%ebp),%eax
 887:	89 45 f0             	mov    %eax,-0x10(%ebp)
  hp->s.size = nu;
 88a:	8b 45 f0             	mov    -0x10(%ebp),%eax
 88d:	8b 55 08             	mov    0x8(%ebp),%edx
 890:	89 50 04             	mov    %edx,0x4(%eax)
  free((void*)(hp + 1));
 893:	8b 45 f0             	mov    -0x10(%ebp),%eax
 896:	83 c0 08             	add    $0x8,%eax
 899:	83 ec 0c             	sub    $0xc,%esp
 89c:	50                   	push   %eax
 89d:	e8 c0 fe ff ff       	call   762 <free>
 8a2:	83 c4 10             	add    $0x10,%esp
  return freep;
 8a5:	a1 68 0c 00 00       	mov    0xc68,%eax
}
 8aa:	c9                   	leave  
 8ab:	c3                   	ret    

000008ac <malloc>:

void*
malloc(uint nbytes)
{
 8ac:	f3 0f 1e fb          	endbr32 
 8b0:	55                   	push   %ebp
 8b1:	89 e5                	mov    %esp,%ebp
 8b3:	83 ec 18             	sub    $0x18,%esp
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
 8b6:	8b 45 08             	mov    0x8(%ebp),%eax
 8b9:	83 c0 07             	add    $0x7,%eax
 8bc:	c1 e8 03             	shr    $0x3,%eax
 8bf:	83 c0 01             	add    $0x1,%eax
 8c2:	89 45 ec             	mov    %eax,-0x14(%ebp)
  if((prevp = freep) == 0){
 8c5:	a1 68 0c 00 00       	mov    0xc68,%eax
 8ca:	89 45 f0             	mov    %eax,-0x10(%ebp)
 8cd:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 8d1:	75 23                	jne    8f6 <malloc+0x4a>
    base.s.ptr = freep = prevp = &base;
 8d3:	c7 45 f0 60 0c 00 00 	movl   $0xc60,-0x10(%ebp)
 8da:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8dd:	a3 68 0c 00 00       	mov    %eax,0xc68
 8e2:	a1 68 0c 00 00       	mov    0xc68,%eax
 8e7:	a3 60 0c 00 00       	mov    %eax,0xc60
    base.s.size = 0;
 8ec:	c7 05 64 0c 00 00 00 	movl   $0x0,0xc64
 8f3:	00 00 00 
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 8f6:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8f9:	8b 00                	mov    (%eax),%eax
 8fb:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 8fe:	8b 45 f4             	mov    -0xc(%ebp),%eax
 901:	8b 40 04             	mov    0x4(%eax),%eax
 904:	39 45 ec             	cmp    %eax,-0x14(%ebp)
 907:	77 4d                	ja     956 <malloc+0xaa>
      if(p->s.size == nunits)
 909:	8b 45 f4             	mov    -0xc(%ebp),%eax
 90c:	8b 40 04             	mov    0x4(%eax),%eax
 90f:	39 45 ec             	cmp    %eax,-0x14(%ebp)
 912:	75 0c                	jne    920 <malloc+0x74>
        prevp->s.ptr = p->s.ptr;
 914:	8b 45 f4             	mov    -0xc(%ebp),%eax
 917:	8b 10                	mov    (%eax),%edx
 919:	8b 45 f0             	mov    -0x10(%ebp),%eax
 91c:	89 10                	mov    %edx,(%eax)
 91e:	eb 26                	jmp    946 <malloc+0x9a>
      else {
        p->s.size -= nunits;
 920:	8b 45 f4             	mov    -0xc(%ebp),%eax
 923:	8b 40 04             	mov    0x4(%eax),%eax
 926:	2b 45 ec             	sub    -0x14(%ebp),%eax
 929:	89 c2                	mov    %eax,%edx
 92b:	8b 45 f4             	mov    -0xc(%ebp),%eax
 92e:	89 50 04             	mov    %edx,0x4(%eax)
        p += p->s.size;
 931:	8b 45 f4             	mov    -0xc(%ebp),%eax
 934:	8b 40 04             	mov    0x4(%eax),%eax
 937:	c1 e0 03             	shl    $0x3,%eax
 93a:	01 45 f4             	add    %eax,-0xc(%ebp)
        p->s.size = nunits;
 93d:	8b 45 f4             	mov    -0xc(%ebp),%eax
 940:	8b 55 ec             	mov    -0x14(%ebp),%edx
 943:	89 50 04             	mov    %edx,0x4(%eax)
      }
      freep = prevp;
 946:	8b 45 f0             	mov    -0x10(%ebp),%eax
 949:	a3 68 0c 00 00       	mov    %eax,0xc68
      return (void*)(p + 1);
 94e:	8b 45 f4             	mov    -0xc(%ebp),%eax
 951:	83 c0 08             	add    $0x8,%eax
 954:	eb 3b                	jmp    991 <malloc+0xe5>
    }
    if(p == freep)
 956:	a1 68 0c 00 00       	mov    0xc68,%eax
 95b:	39 45 f4             	cmp    %eax,-0xc(%ebp)
 95e:	75 1e                	jne    97e <malloc+0xd2>
      if((p = morecore(nunits)) == 0)
 960:	83 ec 0c             	sub    $0xc,%esp
 963:	ff 75 ec             	pushl  -0x14(%ebp)
 966:	e8 dd fe ff ff       	call   848 <morecore>
 96b:	83 c4 10             	add    $0x10,%esp
 96e:	89 45 f4             	mov    %eax,-0xc(%ebp)
 971:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 975:	75 07                	jne    97e <malloc+0xd2>
        return 0;
 977:	b8 00 00 00 00       	mov    $0x0,%eax
 97c:	eb 13                	jmp    991 <malloc+0xe5>
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 97e:	8b 45 f4             	mov    -0xc(%ebp),%eax
 981:	89 45 f0             	mov    %eax,-0x10(%ebp)
 984:	8b 45 f4             	mov    -0xc(%ebp),%eax
 987:	8b 00                	mov    (%eax),%eax
 989:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 98c:	e9 6d ff ff ff       	jmp    8fe <malloc+0x52>
  }
}
 991:	c9                   	leave  
 992:	c3                   	ret    
