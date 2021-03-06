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
                bat 'chcp 850 && msbuild JTransaq.sln /t:Clean;Build /p:Configuration=Release'
            }
        }
        stage('Build.JAR') {
            steps {
                echo 'Check that pipeline-utility-steps Jenkins plugin is installed if you got failure at the next step'
                unzip zipFile: 'JTransaq/src/main/resources/bin/win/x64/txmlconnector64.zip', dir: 'JTransaq/src/main/resources/bin/win/x64'
                bat 'mvn -B -f JTransaq -DskipTests clean package'
                bat 'jar -tf JTransaq/target/JTransaq-0.1.0.jar'
            }
        }
        stage('Test.JAR') {
            steps {
                bat 'mvn -B -f JTransaq test'
            }
            post {
                always {
                    junit '**/target/surefire-reports/*.xml'
                }
            }
        }
        stage('Install.JAR') {
            steps {
                bat 'mvn -B -f JTransaq -DskipTests install'
            }
        }
        stage('Cleanup') {
            steps {
                bat 'chcp 850 && msbuild JTransaq.sln /t:Clean'
                bat 'mvn -B -f JTransaq clean'
                bat 'ant -f JTransaq/build.xml clean'
                bat 'del /Q JTransaq\\src\\main\\resources\\bin\\win\\x64\\txmlconnector64.dll'
            }
        }
    }
}
