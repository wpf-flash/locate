#include <riscv_vector.h>

void MatrixAdd33(data_type A[3][3],data_type B[3][3],data_type c[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			c[i][j]=A[i][j]+B[i][j];
		}
	}
}



////////////intrinsic函数
void MatrixAdd33(data_type A[3][3], data_type B[3][3], data_type C[3][3])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        int n = 3;
        float *ptr_a = &A[i][0];
        float *ptr_b = &B[i][0];
        float *ptr_c = &C[i][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfadd_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

///////////另一种二阶数组intrinsic函数, 也是可以用的，但是是把二维矩阵展开为一维，然后顺序运算!!!!!!!!
void MatrixAdd33(data_type A[3][3], data_type B[3][3], data_type C[3][3])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    
        int n = 3*3;
        float *ptr_a = &A[0][0];// *ptr_a = &A[0][0]
        float *ptr_b = &B[0][0];
        float *ptr_c = &C[0][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfadd_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(ptr_c, vec_c, vl);
        } 
}



