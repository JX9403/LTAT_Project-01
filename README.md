===============================================================
*************************MINI PROJECT 1************************

          Mã nhóm BTL : SNDPROG24PRJ011
          Thành viên 1 : Đoàn Thị Diễm               MSV: B21DCPT075
          Thành viên 2 : Phạm Thị Minh Nguyệt (NT)   MSV: B21DCPT028
          Tiến độ : Đã hoàn thành đủ các yêu cầu.
          Bài : Project #01
	  Link Github : https://github.com/JX9403/LTAT_Project-01
          Yêu cầu :
                - Cài đặt lớp tín hiệu âm thanh
                - Tìm hiểu đọc / ghi file âm thanh
                - Cài đặt:  Các phép toán cơ bản 
                  + Phép dịch thời gian
                  + Phép đảo thời gian
                  + Tăng tần số lấy mẫu
                  + Giảm tần số lấy mẫu
                  + Cộng 2 tín hiệu
                  + Nhân 2 tín hiệu
                  + Tích chập
                - Cài đặt : Bộ lọc nâng cao chất lượng âm thanh
                  + LPS ( Bộ lọc thông thấp)
                  + HPF ( Bộ lọc thông cao)
                  + BPF ( Bộ lọc thông dải)
                  + BSF ( Bộ lọc chắn dải)
                - Cài đặt : Một số hiệu ứng âm thanh  ( tùy chọn )
                  + Tăng 
                  + Giảm
                  + Fade in/out
                  + Echo
                  + Reverb
                  + ...
              
=====================================================================================================================
1. Tổng quan 
  - Mã nguồn gồm các file sau :
    + Mini_project_1.cpp
    + AudioSignal.cpp
    + Wav.cpp 
  - Các file header
    + AudioSignal.h
    + Wav.h 
    + gnuplot-iostream.h ( cần cài đặt thêm, Link cài đặt : 
    https://github.com/dstahlke/gnuplot-iostream/blob/master/gnuplot-iostream.h )

=====================================================================================================================

2. Vai trò và nội dung từng file 
  2.1. Các file header (.h) 
    - Cần được cài đặt trong mục header 
    - Dùng để lưu các khai báo lớp, hàm, biến 
  2.2. Các file mã nguồn ( .cpp )
    a. AudioSignal.cpp 
    - Là file chứa lớp tín hiệu AudioSignal ( gồm các phương thức ( hàm ) đã được khai báo trong file AudioSignal.h)
    b. Wav.cpp 
    - Là file chứa các hàm xử lí file âm thanh ( .wav)
    c. Mini_project_1.cpp
    - Là file chính ( chứa hàm main )
    
=====================================================================================================================
3. Cách thức cài đặt 
* Môi trường :
  - Cài đặt Microsoft Visual Studio 
  - Cài đặt gnuplot
  - Cài đặt vcpkg
  - Tạo Folder Project -> new project -> console app
* Code
  - Thêm các file (.h)  vào mục Header Files
  - Bổ sung file gnuplot-iostream.h 
  - Thêm các file ( .cpp ) vào mục Source Files
  - Chạy chương trình
  ===================Link cài đặt + hướng dẫn chi tiết ============
  Link gnuplot-iostream.h : 
  - Link cài đặt : 
    https://github.com/dstahlke/gnuplot-iostream/blob/master/gnuplot-iostream.h 
  - Hướng dẫn cài đặt môi trường
    https://www.youtube.com/watch?v=gsLIUtmTs8Q&t=150s
  - Tải project tại : Link Github : https://github.com/JX9403/LTAT_Project-01

======================================================================================================================
4. Test Case
Test case 1 : 
  - Mô tả : Phép dịch thời gian
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 1
    + Chọn file wav muốn xử lí
    + Nhập số m 
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe

  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Tín hiệu âm thanh hiển thị sẽ dịch sang trái / phải m đơn vị đã nhập vào tương ứng

Test case 2 :
  - Mô tả : Phép đảo thời gian
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 2
    + Chọn file wav muốn xử lí
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Tín hiệu âm thanh hiển thị được lật ngược lại so với tín hiệu ban đầu
    + Âm thanh thu được ngược lại với âm thanh gốc
Test case 3 :
  - Mô tả : Phép giảm tần số lấy mẫu
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 3
    + Chọn file wav muốn xử lí
    + Chọn M ( tỷ số nén )
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Tín hiệu âm thanh hiển thị sẽ có số lượng mẫu giảm đi M lần
    + Âm thanh thu được sẽ bị giật
Test case 4 :
  - Mô tả : Phép tăng tần số lấy mẫu
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 4
    + Chọn file wav muốn xử lí
    + Chọn L ( tỷ số giãn )
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Tín hiệu âm thanh hiển thị sẽ có số lượng mẫu tăng lên L lần
    + Âm thanh thu được cảm giác âm bị kéo dài ra 
Test case 5 :
  - Mô tả : Phép Cộng 2 tín hiệu
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 5
    + Chọn file wav 1
    + Chọn file Wav 2
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Âm thanh thu được cảm giác 2 file âm thanh cùng được phát
Test case 6 :
  - Mô tả : Phép Nhân 2 tín hiệu
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 6
    + Chọn file wav 1
    + Chọn file Wav 2
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
Test case 7 :
  - Mô tả : Phép Nhân tín hiệu với 1 số 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 7
    + Chọn file wav 
    + Nhập số muốn nhân 
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Âm thanh thu được sẽ to / nhỏ đi tùy vào số đã nhập vào
Test case 8 :
  - Mô tả : Phép tích chập
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 8
    + Chọn file wav 
    + Nhập số muốn nhân 
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Âm thanh thu được sẽ to / nhỏ đi tùy vào số đã nhập vào
    
Test case 9 :
  - Mô tả : Bộ lọc LPF 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 9
    + Chọn file wav 
    + Nhập tần số cắt
    + Nhập bậc của bộ lọc
    + Nhập cửa sổ muốn sử dụng
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Âm thanh thu được cảm giác sẽ trầm thấp hơn âm thanh gốc
Test case 10 :
  - Mô tả : Bộ lọc HPF 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 10
    + Chọn file wav 
    + Nhập tần số cắt
    + Nhập bậc của bộ lọc
    + Nhập cửa sổ muốn sử dụng
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Âm thanh thu được có nhạc nền nhỏ đi, giọng ca sĩ rõ hơn  

Test case 11 :
  - Mô tả : Bộ lọc BPF
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 11
    + Chọn file wav 
    + Nhập tần số cắt 1
    + Nhập tần số cắt 2
    + Nhập bậc của bộ lọc
    + Nhập cửa sổ muốn sử dụng
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 

Test case 12 :
  - Mô tả : Bộ lọc BSF 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 12
    + Chọn file wav 
    + Nhập tần số cắt 1
    + Nhập tần số cắt 2
    + Nhập bậc của bộ lọc
    + Nhập cửa sổ muốn sử dụng
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
Test case 13 :
  - Mô tả : Bộ lọc BSF 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 13
    + Nhập M 
    + Nhập hệ số ak 
    + Chọn y / n để quyết định có lưu file âm thanh cho lần tiếp theo hay không
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý 
    + Âm thanh trả về có tiếng vọng 
Test case 14 :
  - Mô tả : Fade In 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 14
    + Chọn file wav 
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý
    + Âm thanh nhận được sẽ bắt đầu từ nhỏ rồi lớn dần lên 

Test case 15:
  - Mô tả : Increase 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 16
    + Chọn file wav 
    + Nhập số n 
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh đã xử lý
    + Âm thanh nhận được lớn hơn gấp n lần


Test case 16:
  - Mô tả : Vẽ biểu đồ tín hiệu 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 19
    + Chọn file wav 
    + Chọn y / n để quyết định có muốn vẽ biểu đồ hay không.
    + Đợi chương trình xử lí
    + Sau khi đã hiện ra biểu đồ, ấn enter thoát vòng lặp
    + Chọn 21 để lưu file âm thanh vừa xử lý
    + Nhập tên muốn lưu
    + Chọn 20 
    + Chọn âm thanh vừa lưu để nghe
  - Kết quả mong muốn :
    + Hiển thị ra biểu đồ tín hiệu âm thanh của file đã chọn 

Test case 17:
  - Mô tả : Phát âm thanh 
  - Các bước thực hiện : 
    + Chạy chương trình -> Chọn 20
    + Chọn file wav 
    + Chọn file âm thanh muốn phát 
  - Kết quả mong muốn :
    + Âm thanh được phát 
Test case 18:
  - Mô tả : Lưu file âm thanh 
  - Các bước thực hiện : 
    + Cần phải có 1 file âm thanh đã được xử lí và lưu trước đó ( thực hiện 1 trong số các lựa chọn từ 1-20 )
    + Chạy chương trình -> Chọn 21
    + Nhập tên file 
  - Kết quả mong muốn :
    + File âm thanh đã được lưu tại folder assets 
