import sys
import subprocess
from subprocess import Popen

class SvgReceiver:
    """
    A class to receive and process an SVG file transmission via a serial connection.
    """
    
    def __init__(self, team_number: str):
        """
        Initialize the SvgReceiver instance with the specified team number.
        
        Args:
            team_number (str): A team number consisting of 4 to 6 digits.
        """
        self.validate_team_number(team_number)
        self.file_name: str = f"{team_number}.svg"
        self.process: Popen = subprocess.Popen(["serieViaUSB", "-l"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    
    @staticmethod
    def validate_team_number(team_number: str):
        """
        Validate the provided team number.
        
        Args:
            team_number (str): A team number consisting of 4 to 6 digits.
        
        Raises:
            SystemExit: If the team number is invalid.
        """
        if not 3 < len(team_number) < 7 or not team_number.isdigit():
            print("Usage: reception_svg.py TEAM_NUMBER\nTEAM_NUMBER: A team number consisting of 4 to 6 digits.")
            sys.exit(1)
    
    def wait_for_start_byte(self):
        """
        Wait for the start byte to be received from the serial connection.
        """
        print("Waiting for transmission")
        while self.process.stdout.read(1) != b'\x02':
            pass
    
    def write_received_data(self):
        """
        Write the received data to the SVG file until the end-of-text byte is received.
        """
        print("Transmission in progress", end='')
        with open(self.file_name, "w") as file:
            byte: bytes = self.process.stdout.read(1)
            i: int = 0
            while byte != b'\x03':
                if i == 10:
                    print(".", flush=True, end='')
                    i = 0
                i += 1
                file.write(byte.decode("utf-8"))
                byte = self.process.stdout.read(1)

    def display_received_checksum(self):
        """
        Display the received checksum bytes until the end-of-transmission byte is received.
        """
        print("\n\nReceived checksum: ", end='')
        byte: bytes = self.process.stdout.read(1)
        while byte != b'\x04':
            print(byte.decode("utf-8"), end='')
            byte = self.process.stdout.read(1)

    def display_calculated_checksum(self):
        """
        Calculate and display the checksum of the created file.
        """
        print("\nCalculated checksum: ", end='')
        process: Popen = subprocess.Popen(["crc32", self.file_name], stdout=subprocess.PIPE)
        print(process.stdout.read(8).decode("utf-8"))

    def display_svg(self):
        """
        Display the received SVG file in the Firefox browser.
        """
        input("\nPress ENTER to display the SVG...")
        subprocess.run(["firefox", "--kiosk", self.file_name])

def main():
    """
    The main function of the script. It validates the command-line arguments, creates an SvgReceiver instance, and calls its methods.
    """
    if len(sys.argv) != 2:
        print("Usage: reception_svg.py TEAM_NUMBER\nTEAM_NUMBER: A team number consisting of 4 to 6 digits.")
        sys.exit(1)
    receiver: SvgReceiver = SvgReceiver(sys.argv[1])
    receiver.wait_for_start_byte()
    receiver.write_received_data()
    receiver.display_received_checksum()
    receiver.display_calculated_checksum()
    receiver.display_svg()

if __name__ == "__main__":
    main()
