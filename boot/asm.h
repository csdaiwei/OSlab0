/* 参考：i386手册 */
#define GDT_ENTRY(n)  \
	((n) << 3)

#define SEG_NULLASM   \
	.word 0, 0;       \
	.byte 0, 0, 0, 0

#define SEG_ASM(type,base,lim)                              \
	.word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
	.byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
	(0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

//type 表示访问控制？
//GDT每个元素为64 bit 由 Access Base Limit 三者组成
