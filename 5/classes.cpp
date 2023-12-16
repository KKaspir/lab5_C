#include <iostream>
#include <vector>
#include <numeric>
#include <stdexcept>

class Grade {
private:
    std::string subject;
    double score;
    std::string date;


public:
    Grade(const std::string& subj, double scr, const std::string& dt)
        : subject(subj), score(scr), date(dt) {}

    void print() const {
        std::cout << "�������: " << subject << std::endl;
        std::cout << "������: " << score << std::endl;
        std::cout << "����: " << date << std::endl;
    }

    Grade(double score) : score(score) {
        if ((score < 0.0) || (score > 100.0)) {
            throw std::invalid_argument("������ ������ ���� � ��������� [0; 100]!");
        }
    }

    static Grade inputFromConsole() {
        std::string subject;
        double score;
        std::string date;

        std::cout << "������� �������: ";
        std::cin >> subject;
        std::cout << "������� ������: ";
        std::cin >> score;
        std::cout << "������� ����: ";
        std::cin >> date;

        return Grade(subject, score, date);
    }

    double getScore() const {
        return score;
    }

    // �����, ������������ ������ �� ���������
    double* getScorePointer() {
        return &score;
    }

    // �����, ������������ ������ �� ������
    double& getScoreReference() {
        return score;
    }
};



class Student {

private:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string studentID;
    std::string email;
    std::vector<Grade> grades;
public:
    Student(
        const std::string& first,
        const std::string& last,
        const std::string& dob,
        const std::string& id,
        const std::string& mail,
        const std::vector<Grade>& gr
    ) : firstName(first), lastName(last), dateOfBirth(dob), studentID(id), email(mail), grades(gr) {}

    double avgGrade() const {
        if (grades.empty()) {
            return 0.0;
        }
        double totalScore = 0.0;
        for (const Grade& grade : grades) {
            totalScore += grade.getScore();
        }
        return totalScore / grades.size();
    }



    static Student inputFromConsole() {
        std::string first, last, dob, id, mail;
        std::vector<Grade> grades;

        std::cout << "������� ���: ";
        std::cin >> first;
        std::cout << "������� �������: ";
        std::cin >> last;
        std::cout << "������� ���� ��������: ";
        std::cin >> dob;
        std::cout << "������� ����� ������������� ������: ";
        std::cin >> id;
        std::cout << "������� email: ";
        std::cin >> mail;

        char addGrade;
        do {
            Grade grade = Grade::inputFromConsole();
            grades.push_back(grade);

            std::cout << "�������� ��� ���� ������? (y/n): ";
            std::cin >> addGrade;
        } while (addGrade == 'y' || addGrade == 'Y');

        return Student(first, last, dob, id, mail, grades);
    }
    std::string getFirstName() const {
        return firstName;
    }

    std::string getLastName() const {
        return lastName;
    }

    // �����, ������������ ��� � ������� ��������
    std::string getFullName() const {
        return this->firstName + " " + this->lastName;
    }

    // �����, ������������ ������ �� ������
    Grade& getGradeReference() {
        return grades.front(); // ������ ������ ������ ��� �������
    }
    void printStudent(const Student& student) {
        std::cout << "��� � �������: " << student.firstName << " " << student.lastName << std::endl;
        std::cout << "���� ��������: " << student.dateOfBirth << std::endl;
        std::cout << "����� ������������� ������: " << student.studentID << std::endl;
        std::cout << "Email: " << student.email << std::endl;

        std::cout << "\n������:" << std::endl;
        for (const Grade& grade : student.grades) {
            grade.print();
            std::cout << std::endl;
        }
    }

    void inputGrades() {
        try {
            int numGrades;
            std::cout << "������� ���������� ������: ";
            std::cin >> numGrades;

            for (int i = 0; i < numGrades; ++i) {
                double score;
                std::cout << "������� ������ #" << i + 1 << ": ";
                std::cin >> score;

                // ���������� ���������� throw ��� ������������� ���������� ��� ������������ ������
                grades.push_back(Grade(score));
            }
        }
        catch (const std::exception& e) {
            // ������������� ���������� � ������� ��������� �� ������
            std::cerr << "������: " << e.what() << std::endl;
        }
    }
};



class Project {
private:
    std::string projectName;
    std::string description;
    std::string startDate;
    std::string endDate;
    std::vector<Student> teamMembers;

public:
    Project(
        const std::string& name,
        const std::string& desc,
        const std::string& start,
        const std::string& end,
        const std::vector<Student>& members
    ) : projectName(name), description(desc), startDate(start), endDate(end), teamMembers(members) {}

    void addTeamMember(const Student& student) {
        teamMembers.push_back(student);
    }

    void print() const {
        std::cout << "�������� �������: " << projectName << std::endl;
        std::cout << "��������: " << description << std::endl;
        std::cout << "���� ������: " << startDate << std::endl;
        std::cout << "���� ���������: " << endDate << std::endl;

        std::cout << "\n���������:" << std::endl;
        for (const Student& student : teamMembers) {
            std::cout << "���: " << student.getFirstName() << " " << student.getLastName() << std::endl;
        }
    }

    static Project inputFromConsole() {
        std::string name, desc, start, end;
        std::vector<Student> members;

        std::cout << "������� �������� �������: ";
        std::cin >> name;
        std::cout << "������� �������� �������: ";
        std::cin >> desc;
        std::cout << "������� ���� ������: ";
        std::cin >> start;
        std::cout << "������� ���� ���������: ";
        std::cin >> end;

        char addMember;
        do {
            Student student = Student::inputFromConsole();
            members.push_back(student);

            std::cout << "�������� ��� ������ ���������? (y/n): ";
            std::cin >> addMember;
        } while (addMember == 'y' || addMember == 'Y');

        return Project(name, desc, start, end, members);
    }
};

class Event {
private:
    std::string eventName;
    std::string date;
    std::string location;
    std::vector<Student> eventMembers;

public:
    Event(
        const std::string& name,
        const std::string& dt,
        const std::string& loc,
        const std::vector<Student>& members
    ) : eventName(name), date(dt), location(loc), eventMembers(members) {}

    void addParticipant(const Student& student) {
        eventMembers.push_back(student);
    }

    void print() const {
        std::cout << "�������� �����������: " << eventName << std::endl;
        std::cout << "����: " << date << std::endl;
        std::cout << "����� ����������: " << location << std::endl;

        std::cout << "\n���������:" << std::endl;
        for (const Student& student : eventMembers) {
            std::cout << "���: " << student.getFirstName() << " " << student.getLastName() << std::endl;
        }
    }

    static Event inputFromConsole() {
        std::string name, date, location;
        std::vector<Student> members;

        std::cout << "������� �������� �����������: ";
        std::cin >> name;
        std::cout << "������� ���� �����������: ";
        std::cin >> date;
        std::cout << "������� ����� ���������� �����������: ";
        std::cin >> location;

        char addParticipant;
        do {
            Student student = Student::inputFromConsole();
            members.push_back(student);

            std::cout << "�������� ��� ������ ��������� �����������? (y/n): ";
            std::cin >> addParticipant;
        } while (addParticipant == 'y' || addParticipant == 'Y');

        return Event(name, date, location, members);
    }

    std::string getEvenName() const {
        return eventName;
    }

    // ���������� ��������� '+'
    Event operator+(const Event& other) const {
        std::vector<Student> combinedMembers = eventMembers;
        combinedMembers.insert(combinedMembers.end(), other.eventMembers.begin(), other.eventMembers.end());
        return Event(eventName + " & " + other.eventName, date, location, combinedMembers);
    }

    // ���������� ����������� ��������� '++'
    Event& operator++() {
        for (Student& student : eventMembers) {
            student.getGradeReference().getScoreReference() += 1.0;
        }
        return *this;
    }

    // ���������� ������������ ��������� '++'
    Event operator++(int) {
        Event temp = *this;
        ++(*this);
        return temp;
    }
};

class Course {
private:
    std::string courseName;
    std::string startDate;
    std::string endDate;
    std::string instructor;
    std::vector<Event> events;

public:
    Course(
        const std::string& name,
        const std::string& start,
        const std::string& end,
        const std::string& instr,
        const std::vector<Event>& evts
    ) : courseName(name), startDate(start), endDate(end), instructor(instr), events(evts) {}

    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void print() const {
        std::cout << "�������� �����: " << courseName << std::endl;
        std::cout << "���� ������: " << startDate << std::endl;
        std::cout << "���� ���������: " << endDate << std::endl;
        std::cout << "��������������: " << instructor << std::endl;

        std::cout << "�����������: " << std::endl;
        for (const Event& event : events) {
            std::cout << "��������: " << event.getEvenName() << std::endl;
        }
    }

    static Course inputFromConsole() {
        std::string name, start, end, instructor;
        std::vector<Event> events;

        std::cout << "������� �������� �����: ";
        std::cin >> name;
        std::cout << "������� ���� ������ �����: ";
        std::cin >> start;
        std::cout << "������� ���� ��������� �����: ";
        std::cin >> end;
        std::cout << "������� ��� ��������������: ";
        std::cin >> instructor;

        char addEvent;
        do {
            Event event = Event::inputFromConsole();
            events.push_back(event);

            std::cout << "�������� ��� ���� ����������� �����? (y/n): ";
            std::cin >> addEvent;
        } while (addEvent == 'y' || addEvent == 'Y');

        return Course(name, start, end, instructor, events);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        Student student("����", "������", "2000-01-01", "12345", "VAN@example.com", { });
        student.inputGrades();
    }
    catch (const std::exception& e) {
        // ������������� ���������� � ������� ��������� �� ������
        std::cerr << "������ � ������� ����� ���������: " << e.what() << std::endl;
    }

    // �������� ����������� ������� ������
    Grade gradeArray[] = {
        Grade("��������", 4.0, "05.01.2023"),
        Grade("�����", 4.5, "06.01.2023"),
        Grade("���������", 3.5, "07.01.2023")
    };

    std::cout << "\n���������� ������ ������:" << std::endl;
    for (const Grade& g : gradeArray) {
        g.print();
    }

    // �������� ���������� ������� ������
    Grade grade2DArray[2][2] = {
        {Grade("����������", 4.5, "01.01.2023"), Grade("������", 5.0, "02.01.2023")},
        {Grade("�������", 4.0, "03.01.2023"), Grade("����������", 4.5, "04.01.2023")}
    };

    std::cout << "\n��������� ������ ������:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            grade2DArray[i][j].print();
        }
    }

    return 0;
}