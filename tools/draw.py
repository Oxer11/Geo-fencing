import matplotlib.pyplot as plt

# red point -> added point
# blue point -> queried point
# black line -> added polygon
# yellow line -> queried polygon

map_x_min = -2
map_x_max = 10
map_y_min = -2
map_y_max = 8

plt.axis([map_x_min, map_x_max, map_y_min, map_y_max])

print("Hello World!")

fin = open("test.in", "r")
fin.readline()

while True:
    line = fin.readline().strip()
    if not line:
        break
    user_operation = list(map(lambda s: float(s), line.split(" ")))
    if user_operation[0] == 1:
        [operation_type, point_id, x, y] = user_operation
        plt.plot(x, y, 'ro')
    if user_operation[0] == 3:
        [operation_type, x, y] = user_operation
        plt.plot(x, y, 'b.')
    if user_operation[0] == 4:
        n = int(user_operation[2])
        x = []
        y = []
        for i in range(n):
            x.append(user_operation[3 + i * 2])
            y.append(user_operation[4 + i * 2])
        x.append(x[0])
        y.append(y[0])
        plt.plot(x, y, 'k')
    if user_operation[0] == 6:
        n = int(user_operation[1])
        x = []
        y = []
        for i in range(n):
            x.append(user_operation[2 + i * 2])
            y.append(user_operation[3 + i * 2])
        x.append(x[0])
        y.append(y[0])
        plt.plot(x, y, 'y--')

plt.show()

