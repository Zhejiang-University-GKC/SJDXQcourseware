////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

class ImageProcessHelper
{
public:
	//由灰度图得到直方图
	static void CalcHistogram(const GrayData& gData, std::vector<double>& histogram)
	{
		histogram.resize(256);

		int height = gData.GetHeight();
		int width = gData.GetWidth();
		int num = height*width;//总像素数

		//直方图大小，应为256
		int bins = (int)histogram.size();
		for( int i = 0; i < bins; i++ ) {
			histogram[i] = 0.0;
		}

		const uchar* ps = gData.GetAddress();

		for( int i = 0; i < height; i++ ) {
			for( int j = 0; j < width; j++ ) {
				int v = (int)(*ps++);
				histogram[v] ++; //建立直方图
			}
		}

		for( int i = 0; i < bins; i++ ) {
			histogram[i] /= num;//频数化为频率
		}
	}
	//由直方图得到阈值,ostu
	static int CalcThresholdByOstu(const std::vector<double>& histogram) throw()
	{
		assert( histogram.size() == 256 );

		//直方图大小，应为256
		int iBins = (int)histogram.size();

		double variance[256];//类间方差
		double pa = 0.0;//背景出现概率
		double pb = 0.0;//目标出现概率
		double wa = 0.0;//背景平均灰度值
		double wb = 0.0;//目标平均灰度值
		double w0 = 0.0;//全局平均灰度值
		double dData1 = 0.0, dData2 = 0.0;

		::memset(variance, 0, sizeof(variance));

		//计算全局平均灰度值
		for( int i = 0; i < iBins; i ++ ) {
			w0 += (i * histogram[i]);
		}
		//对每个灰度值计算类间方差
		for( int i = 0; i < iBins; i ++ ) {
			pa += histogram[i];
			pb = 1.0 - pa;
			dData1 += (i * histogram[i]);
			dData2 = w0 - dData1;
			wa = dData1 / pa;
			wb = dData2 / pb;
			variance[i] = pa * (wa - w0) * (wa - w0) + pb * (wb - w0) * (wb - w0);
		}
		//遍历，得到类间最大方差对应的灰度值
		double temp = 0.0;
		int threshold = 0;
		for( int i = 0; i < iBins; i ++ ) {
			if( variance[i] > temp ) {
				temp = variance[i];
				threshold = i;
			}
		}

		return threshold;
	}

	static void ErodeBinary(GrayData& gDataSrc, uchar uFore, GrayData& gDataDst)
	{
		gDataDst.Clear();
		if( gDataSrc.IsNull() )
			return ;

		int iH = gDataSrc.GetHeight();
		int iW = gDataSrc.GetWidth();
		gDataDst.Allocate(iW, iH);

		uchar* ps  = gDataSrc.GetAddress();
		uchar* pd  = gDataDst.GetAddress();

		for( int i = 0; i < iH; i ++ ) {  // 
			for( int j = 0; j < iW; j ++ ) {  // 
				if (i > 0 && j > 0) {
					// 左
					if (*(ps+i*iW+j-1) == 0) {
						*(pd+i*iW+j) = 0;
						continue;
					}
					// 右
					if (*(ps+i*iW+j+1) == 0) {
						*(pd+i*iW+j) = 0;
						continue;
					}
					// 上
					if (*(ps+(i-1)*iW+j) == 0) {
						*(pd+i*iW+j) = 0;
						continue;
					}
					// 下
					if (*(ps+(i+1)*iW+j) == 0) {
						*(pd+i*iW+j) = 0;
						continue;
					}
					*(pd+i*iW+j) = uFore;
				}
			}
		}
	}
	static void DilateBinary(GrayData& gDataSrc, uchar uFore, GrayData& gDataDst)
	{
		gDataDst.Clear();
		if( gDataSrc.IsNull() )
			return ;

		int iH = gDataSrc.GetHeight();
		int iW = gDataSrc.GetWidth();
		gDataDst.Allocate(iW, iH);

		uchar* ps  = gDataSrc.GetAddress();
		uchar* pd  = gDataDst.GetAddress();

		for( int i = 0; i < iH; i ++ ) {
			for( int j = 0; j < iW; j ++ ) {
				if (i > 0 && j > 0) {
					// 左
					if (*(ps+i*iW+j-1) == uFore) {
						*(pd+i*iW+j) = uFore;
						continue;
					}
					// 右
					if (*(ps+i*iW+j+1) == uFore) {
						*(pd+i*iW+j) = uFore;
						continue;
					}
					// 上
					if (*(ps+(i-1)*iW+j) == uFore) {
						*(pd+i*iW+j) = uFore;
						continue;
					}
					// 下
					if (*(ps+(i+1)*iW+j) == uFore) {
						*(pd+i*iW+j) = uFore;
						continue;
					}
					*(pd+i*iW+j) = 0;
				}
			}
		}
	}

private:
	//连通域标记算法,标记出连通域
	//给出种子点的标记
	static int label_one_growing(int iLabel, int x, int y, const GrayData& gData, std::vector<int>& matrix)
	{
		const uchar* ps = gData.GetAddress();
		int height = gData.GetHeight();
		int width = gData.GetWidth();
		int count = 0;

		std::stack<std::pair<int, int>> coordinate_stack;
		coordinate_stack.push(std::make_pair(y, x));
		matrix[y * width + x] = iLabel;

		int t_ps;
		//区域增长,白色，没有标记过
		while( !coordinate_stack.empty() ) {
			std::pair<int, int> t_coordinate = coordinate_stack.top();
			coordinate_stack.pop();
			int t_y = t_coordinate.first;  //height, y
			int t_x = t_coordinate.second; //width, x
			int n_y;
			int n_x;

			n_y = t_y;
			//左边
			n_x = t_x - 1;
			if( n_x >= 0 ) {
				t_ps = (int)(*(ps + n_y * width + n_x));
				if( t_ps != 0 && matrix[n_y * width + n_x] == 0 ) {
					matrix[n_y * width + n_x] = iLabel;
					coordinate_stack.push(std::make_pair(n_y, n_x));
				}
			}
			//右边
			n_x = t_x + 1;
			if( n_x < width ) {
				t_ps = (int)(*(ps + n_y * width + n_x));
				if( t_ps != 0 && matrix[n_y * width + n_x] == 0 ) {
					matrix[n_y * width + n_x] = iLabel;
					coordinate_stack.push(std::make_pair(n_y, n_x));
				}
			}
			n_x = t_x;
			//上边
			n_y = t_y - 1;
			if( n_y >= 0 ) {
				t_ps = (int)(*(ps + n_y * width + n_x));
				if( t_ps != 0 && matrix[n_y * width + n_x] == 0 ) {
					matrix[n_y * width + n_x] = iLabel;
					coordinate_stack.push(std::make_pair(n_y, n_x));
				}
			}
			//下边
			n_y = t_y + 1;
			if( n_y < height ) {
				t_ps = (int)(*(ps + n_y * width + n_x));
				if( t_ps != 0 && matrix[n_y * width + n_x] == 0 ) {
					matrix[n_y * width + n_x] = iLabel;
					coordinate_stack.push(std::make_pair(n_y, n_x));
				}
			}

			count ++;
		}

		return count;
	}

public:
	//所有都标记
	static int Label(const GrayData& gData, std::vector<int>& matrix, std::vector<int>& vecArea)
	{
		const uchar* ps = gData.GetAddress();
		int height = gData.GetHeight();
		int width = gData.GetWidth();

		matrix.resize(width * height);  //overflow?

		for( int i = 0; i < height; i ++ ) {
			for( int j = 0; j < width; j ++ ) {
				matrix[i * width + j] = 0;
			}
		}

		//面积表初始化
		vecArea.clear();
		vecArea.push_back(0);

		int t_ps;
		int label = 0;
		//执行完成后，若matrix[i * width + j]的值为0，则表明这块区域是黑色，否则相同标号的为同一区域
		for( int i = 0; i < height; i ++ ) {
			for( int j = 0; j < width; j ++ ) {
				t_ps = (int)(*(ps + i * width + j));
				if( t_ps != 0 && matrix[i * width + j] == 0 ) {
					label ++;
					//获得一个种子点
					int count = label_one_growing(label, j, i, gData, matrix);
					//记录面积表
					vecArea.push_back(count);
				}
			}
		}
		return label;
	}

	//extract border
	static int ExtractBorder(uchar uBorderValue, GrayData& gData) throw()
	{
		const int c_coord_x[] = { -1,  0,  1, -1, 1, -1, 0, 1 };
		const int c_coord_y[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
		const int c_num = 8;
		int count = 0;
		uchar* pd = gData.GetAddress();
		uchar* p0 = pd;
		int iW = gData.GetWidth();
		int iH = gData.GetHeight();
		for( int i = 0; i < iH; i ++ ) {
			for( int j = 0; j < iW; j ++ ) {
				if( *pd != 0 ) {
					for( int m = 0; m < c_num; m ++ ) {
						int x = j + c_coord_x[m];
						int y = i + c_coord_y[m];
						if( x < 0 || x >= iW || y < 0 || y >= iH
							|| p0[y * iW + x] == 0 ) {
							*pd = uBorderValue; // Border Mask
							count ++;
							break;
						}
					}
				}
				pd ++;
			}
		}
		return count;
	}
	//cancel border
	static void CancelBorder(uchar uBorderValue, uchar uForeValue, GrayData& gData) throw()
	{
		uchar* pd = gData.GetAddress();
		int iW = gData.GetWidth();
		int iH = gData.GetHeight();
		for( int i = 0; i < iH; i ++ ) {
			for( int j = 0; j < iW; j ++ ) {
				if( *pd == uBorderValue )
					*pd = uForeValue;
				pd ++;
			}
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
