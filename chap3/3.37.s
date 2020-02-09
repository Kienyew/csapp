// int mat1[M][N];
// int mat2[N][M];

// int sum_element(int i, int j) {
// 	return mat1[i][j] + mat2[j][i];
// }

movl	8(%ebp), %ecx		# save i to %ecx
movl	12(%ebp), %edx		# save j to %edx
leal	0(,%ecx,8), %eax	# save 8i to %eax
subl	%ecx, %eax			# %eax = 8i - i = 7i
addl	%edx, %eax			# %eax = 7i + j
leal	(%edx,%edx,4), %edx	# %edx = 5j
addl	%ecx, %edx			# %edx = i + 5j
movl	mat1(,%eax,4), %eax	# %eax = mat1 + 28i + 4j
addl	mat2(,%edx,4), %eax # %eax += mat2 + 4i + 20j

# ALGEBRA
# 4Ni + 4Mj = 28i + 4j
# N = 7, M = 5

