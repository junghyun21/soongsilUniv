# [과제 1] 간단한 영상처리

> 세부 과제

1. sample.jpg 파일을 grayscale로 열어서 이미지의 평균 밝기 보다 어두운 픽셀들을 0으로 바꿔서 output.jpg로 저장하기
    - [source](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/cv/project1/project1-1.py)
2. sample.jpg 파일에 대해서 이미지 평균 밝기를 기준으로 하여 명암비를 조절한 결과를 contrast.jpg로 저장하기
    - 명암비 조절 방식은 원본의 pixel 값에 일정한 값을 곱하는 형태로 진행
    - 계수는 2.0
    - 결과 저장 시 saturation 연산 적용
    - [source](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/cv/project1/project1-2.py)
3. 웹캠을 사용하여 카메라로부터 들어오는 현재 프레임이 직전 프레임보다 이미지 전체의 평균 밝기가 30 넘게 바뀔 경우, 그 시점부터 다음 3초간 반전시켜서 output.avi로 저장하기
    - [source](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/cv/project1/project1-3.py)


