class System:
    def __init__(self, init_time=0, init_value=0, timestep=1000):
        self._time = init_time
        self._value = init_value
        self._timestep = timestep

    def get_time(self):
        return self._time

    def get_state(self):
        return 1 + 2 * (int(self._value) / 4096 * 3.3 + 0.02)
        # return 1 + 2 * self._value

    def set_value(self, value):
        self._value = value
        self._time += self._timestep


system = System(init_time=1000, init_value=500)


class Pid:
    def __init__(self, kp, ki, kd, min_output, max_output):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.min_output = min_output
        self.max_output = max_output
        self.prev_error = 0
        self.prev_time = 0
        self._ierror = 0

    def update(self, target):
        state = system.get_state()
        error = target - state

        dt = system.get_time() - self.prev_time

        output = self.kp * error

        if dt > 0:
            self._ierror += error * dt
            output += self.ki * self._ierror
            output += self.kd * (error - self.prev_error) / dt

        if output > self.max_output:
            output = self.max_output
        elif output < self.min_output:
            output = self.min_output

        self.prev_error = error
        self.prev_time = system.get_time()

        system.set_value(output)

        return system.get_state()


def main():
    pid = Pid(2.0, 0.2, 0.0, 0, 4095)

    states = [pid.update(5) for _ in range(20)]
    print(states)


if __name__ == "__main__":
    main()
