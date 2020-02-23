pipeline {
    agent {
        label 'windows-msbuild'
    }
    stages {
        stage('Prepare') {
            steps {
                bat 'set'
            }
        }
        stage('Build.DLL') {
            steps {
                bat 'chcp 850 && msbuild JTransaq.sln /t:Build /p:Configuration=Release'
            }
        }
        stage('Build.JAR') {
            steps {
                unzip zipFile: 'src/main/resources/bin/win/x64/txmlconnector64.zip' dir: 'src/main/resources/bin/win/x64'
                bat 'mvn -B -f JTransaq -DskipTests package'
                bat 'jar -tf JTransaq/target/JTransaq-0.1.0.jar'
            }
        }
        stage('Test.JAR') {
            steps {
                bat 'mvn -B -f JTransaq test'
            }
        }
    }
}
