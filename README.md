**Xử Lý Dữ Liệu MNIST và Thuật Toán k-Nearest Neighbors (kNN)**
**Giới Thiệu**
Đây là bài tập lớn cho môn Cấu trúc dữ liệu và giải thuật tại Trường Đại học Bách Khoa TP.HCM. Mục tiêu của bài tập là làm quen với thuật toán phân loại k-nearest neighbors (kNN) và áp dụng thuật toán này để xử lý và phân loại dữ liệu từ bộ dữ liệu MNIST, thông qua việc sử dụng cấu trúc dữ liệu danh sách.

**Mục Tiêu**
Sau khi hoàn thành bài tập, sinh viên sẽ:
+ Thành thạo lập trình hướng đối tượng.
+ Sử dụng thành thạo cấu trúc dữ liệu danh sách.
+ Hiểu và thực hiện thuật toán kNN để phân loại dữ liệu.

**Nội Dung Bài Tập**
Tập Dữ Liệu MNIST:
Bộ dữ liệu MNIST bao gồm các hình ảnh viết tay của các chữ số từ 0 đến 9 với kích thước 28x28 pixel.
Dữ liệu được lưu trữ dưới dạng các giá trị pixel từ 0 đến 255, mỗi hình ảnh đi kèm với một nhãn từ 0 đến 9.

Thuật Toán k-Nearest Neighbors (kNN):
kNN là một thuật toán phân loại dựa trên việc tìm kiếm k điểm dữ liệu gần nhất để phân loại dữ liệu mới.
Khoảng cách giữa các điểm dữ liệu được tính bằng khoảng cách Euclidean.


Để biên dịch và chạy chương trình, trước tiên bạn cần cài đặt môi trường có sẵn trình biên dịch C++ (cụ thể là g++ với chuẩn C++11). Sau khi đã chuẩn bị môi trường, bạn có thể biên dịch chương trình bằng cách sử dụng lệnh sau trong terminal:

bash:
g++ -o main main.cpp kNN.cpp -I . -std=c++11
Lệnh này sẽ tạo ra một file thực thi có tên là main. Sau khi biên dịch thành công, bạn có thể chạy chương trình bằng cách gõ lệnh:

bash
./main
